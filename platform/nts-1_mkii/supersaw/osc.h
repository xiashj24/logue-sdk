#pragma once
/*
    BSD 3-Clause License

    Copyright (c) 2023, KORG INC.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    * Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//*/

/*
 *  File: osc.h
 *
 *  Dummy oscillator template instance.
 *
 */

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <climits>

#include "unit_osc.h"   // Note: Include base definitions for osc units

#include "utils/int_math.h"   // for clipminmaxi32()
#include "daisysp.h"

class Osc {
 public:
  /*===========================================================================*/
  /* Public Data Structures/Types/Enums. */
  /*===========================================================================*/

  enum {
    SPREAD = 0U,
    MIX,
    NOISE, 
    ALGO,
    NUM_PARAMS
  };

  enum SAW_ALGO {
    NAIVE = 0,
    POLYBLEP,
    WAVETABLE,
    NUM_ALGO,
  };

  // Note: Make sure that default param values correspond to declarations in header.c
  struct Params {
    float spread{0.5f};
    float mix{0.f};
    float noise{0.f};
    SAW_ALGO algo{NAIVE};

    void reset() {
      spread = 0.5f;
      mix = 0.f;
      noise = 0.f;
      algo = NAIVE;
    }
  };



  /*===========================================================================*/
  /* Lifecycle Methods. */
  /*===========================================================================*/

  Osc(void) {}
  ~Osc(void) {} // Note: will never actually be called for statically allocated instances

  inline int8_t Init(const unit_runtime_desc_t * desc) {
    if (!desc)
      return k_unit_err_undef;
    
    // Note: make sure the unit is being loaded to the correct platform/module target
    if (desc->target != unit_header.target)
      return k_unit_err_target;
    
    // Note: check API compatibility with the one this unit was built against
    if (!UNIT_API_IS_COMPAT(desc->api))
      return k_unit_err_api_version;

    // Check compatibility of samplerate with unit, for NTS-1 MKII should be 48000
    if (desc->samplerate != 48000)
      return k_unit_err_samplerate;

    // Check compatibility of frame geometry
    // Note: NTS-1 mkII oscillators can make use of the audio input depending on the routing options in global settings, see product documentation for details.
    if (desc->input_channels != 2 || desc->output_channels != 1)  // should be stereo input / mono output
      return k_unit_err_geometry;

    // Note: SDRAM is not available from the oscillator runtime environment
    
    // Cache the runtime descriptor for later use
    runtime_desc_ = *desc;

    // Make sure parameters are reset to default values
    params_.reset();

    for (int i = 0; i < OSC_NUM; ++i)
    {
      osc_bank[i].Init(k_samplerate);
      osc_bank[i].SetWaveform(daisysp::Oscillator::WAVE_SAW);
      osc_bank[i].SetAmp(1.f);
      osc_bank[i].PhaseAdd((float)i/(float)OSC_NUM);
    }

    noise.Init();

    for (int i = 0; i < HPF_ORDER; ++i)
    {
      hpf[i].Init();
      hpf[i].SetFilterMode(daisysp::OnePole::FILTER_MODE_HIGH_PASS);
    }

    for (int i = 0; i < LPF_ORDER; ++i)
    {
      lpf_noise[i].Init();
      lpf_noise[i].SetFilterMode(daisysp::OnePole::FILTER_MODE_LOW_PASS);
      lpf_noise[i].SetFrequency(NOISE_LPF_FREQ); // smooth out some highend
    } 

    return k_unit_err_none;
  }

  inline void Teardown() {
    // Note: cleanup and release resources if any
  }

  inline void Reset() {
    // Note: Reset effect state, excluding exposed parameter values.
  }

  inline void Resume() {
    // Note: Effect will resume and exit suspend state. Usually means the synth
    // was selected and the render callback will be called again
  }

  inline void Suspend() {
    // Note: Effect will enter suspend state. Usually means another effect was
    // selected and thus the render callback will not be called
  }

  /*===========================================================================*/
  /* Other Public Methods. */
  /*===========================================================================*/

  fast_inline void Process(const float * in, float * out, size_t frames) {
    const float * __restrict in_p = in;
    float * __restrict out_p = out;
    const float * out_e = out_p + frames;  // assuming mono output

    // Caching current parameter values. Consider interpolating sensitive parameters.
    const Params p = params_;

    // get osc pitch from context
    const unit_runtime_osc_context_t *ctxt = static_cast<const unit_runtime_osc_context_t *>(runtime_desc_.hooks.runtime_context);
    float w0 = osc_w0f_for_note((ctxt->pitch)>>8, ctxt->pitch & 0xFF);
    float lfo = q31_to_f32(ctxt->shape_lfo);
    float f0 = w0 * k_samplerate;

    float detune = linintf(clip01f(p.spread+lfo), 0.01f, 0.5f);
    float mix = linintf(p.mix, 0.f, 1.f);
    float noise_fm_depth = linintf(p.noise, 0.0001f, 0.01f);

    for (int i = 0; i < HPF_ORDER; ++i)
    {
      hpf[i].SetFrequency(w0 * 0.5); // 50% key tracking hpf to remove aliasing below f0
    }


    for (int i = 0; i < OSC_NUM; ++i)
    {
      int pos = i - (OSC_NUM-1)/2;
      osc_bank[i].SetFreq(f0 + pos*detune);

      float osc_relative_amp = 1.f - (float)pos / ((OSC_NUM+1)/2);
      // float osc_relative_amp = 1.f;
      if (pos != 0)
      {
        osc_bank[i].SetAmp(osc_relative_amp*mix);
      }

      if (p.algo == NAIVE)
      {
        osc_bank[i].SetWaveform(daisysp::Oscillator::WAVE_SAW);
      }
      else if (p.algo == POLYBLEP)
      {
        osc_bank[i].SetWaveform(daisysp::Oscillator::WAVE_POLYBLEP_SAW);
      }
      else if (p.algo == WAVETABLE)
      {
        osc_bank[i].SetWaveform(daisysp::Oscillator::WAVE_TABLE_SAW);
      }
    }

    for (; out_p != out_e; in_p += 2, out_p += 1) {
      // Process/generate samples here
      
      // fm by noise
      for (int i = 0; i < OSC_NUM; ++i)
      {
        float noise_filtered = noise.Process();
        for (int i = 0; i < LPF_ORDER; ++i)
        {
          noise_filtered = lpf_noise[i].Process(noise_filtered);
        }
        osc_bank[i].PhaseAdd(noise_fm_depth * noise_filtered);
      }

      float osc_mix = 0.f;

      for (int i = 0; i < OSC_NUM; ++i)
      {
        osc_mix += osc_bank[i].Process();
      }
      
      float hpf_out = osc_mix;
      for (int i = 0; i < HPF_ORDER; ++i)
      {
        hpf_out = hpf[i].Process(hpf_out);
      }
      
      float output = hpf_out;

      *out_p = output;
    }
  }

  inline void setParameter(uint8_t index, int32_t value) {
    switch (index) {
    case SPREAD:
      // 10bit 0-1023 parameter
      value = clipminmaxi32(0, value, 1023);
      params_.spread = param_10bit_to_f32(value); // 0 .. 1023 -> 0.0 .. 1.0
      break;

    case MIX:
      // 10bit 0-1023 parameter
      value = clipminmaxi32(0, value, 1023);
      params_.mix = param_10bit_to_f32(value); // 0 .. 1023 -> 0.0 .. 1.0
      break;

    case NOISE:
      // 10bit 0-1023 parameter
      value = clipminmaxi32(0, value, 1023);
      params_.noise = param_10bit_to_f32(value); // 0 .. 1023 -> 0.0 .. 1.0
      break;

    case ALGO:
      // strings type parameter, receiving index value
      value = clipminmaxi32(0, value, SAW_ALGO::NUM_ALGO-1);
      params_.algo = (SAW_ALGO)value;
      break;
      
    default:
      break;
    }
  }

  inline int32_t getParameterValue(uint8_t index) const {
    switch (index) {
    case SPREAD:
      // 10bit 0-1023 parameter
      return param_f32_to_10bit(params_.spread);
      break;

    case MIX:
      // 10bit 0-1023 parameter
      return param_f32_to_10bit(params_.mix);
      break;

    case NOISE:
      // 10bit 0-1023 parameter
      return param_f32_to_10bit(params_.noise);
      break;

    case ALGO:
      // strings type parameter, return index value
      return params_.algo;

    default:
      break;
    }

    return INT_MIN; // Note: will be handled as invalid
  }

  inline const char * getParameterStrValue(uint8_t index, int32_t value) const {
    // Note: String memory must be accessible even after function returned.
    //       It can be assumed that caller will have copied or used the string
    //       before the next call to getParameterStrValue
    
    static const char * algo_strings[SAW_ALGO::NUM_ALGO] = {
      "NAIVE",
      "POLYBELP",
      "WAVETABLE"
    };
    
    switch (index) {
    case ALGO:
      if (value >= 0 && value < SAW_ALGO::NUM_ALGO)
        return algo_strings[value];
      break;
    default:
      break;
    }
    
    return nullptr;
  }

  inline void setTempo(uint32_t tempo) {
    // const float bpmf = (tempo >> 16) + (tempo & 0xFFFF) / static_cast<float>(0x10000);
    (void)tempo;
  }

  inline void tempo4ppqnTick(uint32_t counter) {
    (void)counter;
  }

  inline void NoteOn(uint8_t note, uint8_t velo) {
    (uint8_t)note;
    (uint8_t)velo;
  }

  inline void NoteOff(uint8_t note) {
    (uint8_t)note;
  }

  inline void AllNoteOff() {
  }

  inline void PitchBend(uint8_t bend) {
    (uint8_t)bend;
  }

  inline void ChannelPressure(uint8_t press) {
    (uint8_t)press;
  }

  inline void AfterTouch(uint8_t note, uint8_t press) {
    (uint8_t)note;
    (uint8_t)press;
  }

  
  /*===========================================================================*/
  /* Static Members. */
  /*===========================================================================*/
  
 private:
  /*===========================================================================*/
  /* Constants. */
  /*===========================================================================*/
  // detune interval in hz
  static constexpr int OSC_NUM = 7;
  static constexpr int HPF_ORDER = 4;
  static constexpr int LPF_ORDER = 1;
  static constexpr float NOISE_LPF_FREQ = 0.2f;

  /*===========================================================================*/
  /* Private Member Variables. */
  /*===========================================================================*/

  std::atomic_uint_fast32_t flags_;

  unit_runtime_desc_t runtime_desc_;

  Params params_;

  daisysp::Oscillator osc_bank[OSC_NUM];
  daisysp::WhiteNoise noise;
  daisysp::OnePole hpf[HPF_ORDER];
  daisysp::OnePole lpf_noise[LPF_ORDER];


  // daisysp::Svf svf;

  // daisysp::SquareNoise hihat;

  /*===========================================================================*/
  /* Private Methods. */
  /*===========================================================================*/

};
