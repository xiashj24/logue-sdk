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
 *  File: modfx.h
 *
 *  Dummy modulation effect template instance.
 *
 */

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <climits>

#include "unit_modfx.h"   // Note: Include base definitions for modfx units

#include "utils/buffer_ops.h" // for buf_clr_f32()
#include "utils/int_math.h"   // for clipminmaxi32()

#include "korg35.h"
// #include "ladder.h"
// #include "oberheim.h"
// #include "sallenkey.h"

class Modfx {
 public:
  /*===========================================================================*/
  /* Public Data Structures/Types/Enums. */
  /*===========================================================================*/

  enum {
    BUFFER_LENGTH = 0x8000U,
  };

  enum {
    CUTOFF = 0U,
    RESONANCE,
    MODE, 
    NUM_PARAMS
  };

  // Note: Make sure that default param values correspond to declarations in header.c
  struct Params {
    float cutoff{1.f};
    float res{0.f};
    korg35::FilterMode mode{korg35::LP};

    void reset() {
      cutoff = 1.f;
      res = 0.f;
      mode = korg35::LP;
    }
  };

  /*===========================================================================*/
  /* Lifecycle Methods. */
  /*===========================================================================*/

  Modfx(void) {}
  ~Modfx(void) {} // Note: will never actually be called for statically allocated instances

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
    if (desc->input_channels != 2 || desc->output_channels != 2)  // should be stereo input/output
      return k_unit_err_geometry;

    // If SDRAM buffers are required they must be allocated here
    if (!desc->hooks.sdram_alloc)
      return k_unit_err_memory;
    float *m = (float *)desc->hooks.sdram_alloc(BUFFER_LENGTH * sizeof(float));
    if (!m)
      return k_unit_err_memory;

    // Make sure buffer is cleared
    buf_clr_f32(m, BUFFER_LENGTH);

    allocated_buffer_ = m;
    
    // Cache the runtime descriptor for later use
    runtime_desc_ = *desc;

    // Make sure parameters are reset to default values
    params_.reset();

    filter.init(desc->samplerate);

    return k_unit_err_none;
  }

  inline void Teardown() {
    // Note: buffers allocated via sdram_alloc are automatically freed after unit teardown
    // Note: cleanup and release resources if any
    allocated_buffer_ = nullptr;
  }

  inline void Reset() {
    // Note: Reset effect state, excluding exposed parameter values.
  }

  inline void Resume() {
    // Note: Effect will resume and exit suspend state. Usually means the synth
    // was selected and the render callback will be called again

    // Note: If it is required to clear large memory buffers, consider setting a flag
    //       and trigger an asynchronous progressive clear on the audio thread (Process() handler)
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
    const float * out_e = out_p + (frames << 1);  // assuming stereo output

    // Caching current parameter values. Consider interpolating sensitive parameters.
    const Params p = params_;

    // smoothing is now handled inside the korg35.compute() function
    // float freq_target = linintf(p.time, 0.f, 1.f);
    // float res_target = linintf(p.depth, 0.f, 1.f);
    // freq = linintf(0.03f, freq, freq_target);
    // res = linintf(0.03f, res, res_target);

    filter.setFreqNormalized(p.cutoff);
    filter.setResonance(p.res);
    filter.setMode(p.mode);

    float stereo_buffer_left_in[FRAME_SIZE];
    float stereo_buffer_right_in[FRAME_SIZE];
    float* stereo_buffer_in[2] = {stereo_buffer_left_in, stereo_buffer_right_in};

    float stereo_buffer_left_out[FRAME_SIZE];
    float stereo_buffer_right_out[FRAME_SIZE];
    float* stereo_buffer_out[2] = {stereo_buffer_left_out, stereo_buffer_right_out};

    // de-interleave buffer
    for (int i = 0; i < 64; ++i, in_p += 2)
    {
      stereo_buffer_in[0][i] = in_p[0];
      stereo_buffer_in[1][i] = in_p[1];
    }
    
    // process frame
    filter.compute(FRAME_SIZE, stereo_buffer_in, stereo_buffer_out);

    // interleave buffer
    for (int i = 0; i < 64; ++i, out_p += 2)
    {
      out_p[0] = stereo_buffer_out[0][i];
      out_p[1] = stereo_buffer_out[1][i];
    }
  }

  inline void setParameter(uint8_t index, int32_t value) {
    switch (index) {
    case CUTOFF:
      // 10bit 0-1023 parameter
      value = clipminmaxi32(0, value, 1023);
      params_.cutoff = param_10bit_to_f32(value); // 0 .. 1023 -> 0.0 .. 1.0
      break;

    case RESONANCE:
      // 10bit 0-1023 parameter
      value = clipminmaxi32(0, value, 1023);
      params_.res = param_10bit_to_f32(value); // 0 .. 1023 -> 0.0 .. 1.0
      break;

    case MODE:
      // strings type parameter, receiving index value
      value = clipminmaxi32(0, value, korg35::NUM_MODE-1);
      params_.mode = korg35::FilterMode(value);
      break;
      
    default:
      break;
    }
  }

  inline int32_t getParameterValue(uint8_t index) const {
    switch (index) {
    case CUTOFF:
      // 10bit 0-1023 parameter
      return param_f32_to_10bit(params_.cutoff);
      break;

    case RESONANCE:
      // 10bit 0-1023 parameter
      return param_f32_to_10bit(params_.res);
      break;

    case MODE:
      // strings type parameter, return index value
      return params_.mode;

    default:
      break;
    }

    return INT_MIN; // Note: will be handled as invalid
  }

  inline const char * getParameterStrValue(uint8_t index, int32_t value) const {
    // Note: String memory must be accessible even after function returned.
    //       It can be assumed that caller will have copied or used the string
    //       before the next call to getParameterStrValue
    
    static const char * param3_strings[korg35::NUM_MODE] = {
      "LP",
      "BP",
      "HP",
    };
    
    switch (index) {
    case MODE:
      if (value >= 0 && value < korg35::NUM_MODE)
        return param3_strings[value];
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
  
  /*===========================================================================*/
  /* Static Members. */
  /*===========================================================================*/
  
 private:
  /*===========================================================================*/
  /* Private Member Variables. */
  /*===========================================================================*/

  std::atomic_uint_fast32_t flags_;

  unit_runtime_desc_t runtime_desc_;

  Params params_;
  
  float * allocated_buffer_;

  float freq {1.f};
  float res {0.f};

  korg35 filter;
  // ladder filter;
  // oberheim filter;
  // sallenkey filter;
  
  /*===========================================================================*/
  /* Private Methods. */
  /*===========================================================================*/

  /*===========================================================================*/
  /* Constants. */
  /*===========================================================================*/
  static constexpr int FRAME_SIZE = 64;

};
