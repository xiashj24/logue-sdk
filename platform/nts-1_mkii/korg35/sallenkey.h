/* ------------------------------------------------------------
name: "sallenkey"
Code generated with Faust 2.72.14 (https://faust.grame.fr)
Compilation options: -lang cpp -nvi -ct 1 -cn sallenkey -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */


#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS sallenkey
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class sallenkey {
	
 private:
	
	float freq_norm_;
	float res_;
	int fSampleRate;
	float fConst0;
	float fRec1[2];
	float fRec2[2];
	
 public:
	sallenkey() {}

	void setFreqNormalized(float freq)
	{
		freq_norm_ = freq;
	}

	void setResonance(float res)
	{
		res_ = res;
	}

	static constexpr int getStaticNumInputs() {
		return 2;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 2;
	}
	int getNumOutputs() {
		return 2;
	}
	
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 6.2831855f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		freq_norm_ = float(1.0f);
		res_ = float(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
	}
	
	void init(int sample_rate) {
		instanceInit(sample_rate);
	}
	
	void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	// void buildUserInterface(UI* ui_interface) {
	// 	ui_interface->openVerticalBox("sallenkey");
	// 	ui_interface->addHorizontalSlider("freq", &freq_norm_, float(1.0f), float(0.0f), float(1.0f), float(0.001f));
	// 	ui_interface->addHorizontalSlider("resonance", &res_, float(0.0f), float(0.0f), float(1.0f), float(0.001f));
	// 	ui_interface->closeBox();
	// }
	
	void compute(int count, float** RESTRICT inputs, float** RESTRICT outputs) {
		float* input0 = inputs[0];
		float* input1 = inputs[1];
		float* output0 = outputs[0];
		float* output1 = outputs[1];
		float fSlow0 = std::tan(fConst0 * std::pow(1e+01f, 3.0f * float(freq_norm_) + 1.0f));
		float fSlow1 = 1.0f / (24.293f * float(res_) + 0.707f) + fSlow0;
		float fSlow2 = fSlow0 * fSlow1 + 1.0f;
		float fSlow3 = fSlow0 / fSlow2;
		float fSlow4 = 2.0f * fSlow3;
		float fSlow5 = 2.0f * fSlow0;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]) + float(input1[i0]) - (fRec2[1] + fSlow1 * fRec1[1]);
			float fTemp1 = fRec1[1] + fSlow4 * fTemp0;
			float fRec0 = fRec2[1] + fSlow0 * fTemp1;
			fRec1[0] = fTemp1;
			float fTemp2 = fRec1[1] + fSlow3 * fTemp0;
			fRec2[0] = fRec2[1] + fSlow5 * fTemp2;
			float fTemp3 = 0.5f * fRec0;
			output0[i0] = float(fTemp3);
			output1[i0] = float(fTemp3);
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
		}
	}

};