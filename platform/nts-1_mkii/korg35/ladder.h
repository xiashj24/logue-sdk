/* ------------------------------------------------------------
name: "moogladder"
Code generated with Faust 2.72.14 (https://faust.grame.fr)
Compilation options: -lang cpp -nvi -ct 1 -cn ladder -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float ladder_faustpower4_f(float value) {
	return value * value * value * value;
}

class ladder {
	
 private:
	
	float freq_norm_;
	float res_;
	float fRec0[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	int fSampleRate;
	
 public:
	ladder() {}

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
	}
	
	void instanceResetUserInterface() {
		freq_norm_ = float(1.0f);
		res_ = float(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
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
	// 	ui_interface->openVerticalBox("moogladder");
	// 	ui_interface->addHorizontalSlider("freq", &freq_norm_, float(1.0f), float(0.0f), float(1.0f), float(0.001f));
	// 	ui_interface->addHorizontalSlider("resonance", &res_, float(0.0f), float(0.0f), float(1.0f), float(0.001f));
	// 	ui_interface->closeBox();
	// }
	
	void compute(int count, float** RESTRICT inputs, float** RESTRICT outputs) {
		float* input0 = inputs[0];
		float* input1 = inputs[1];
		float* output0 = outputs[0];
		float* output1 = outputs[1];
		float fSlow0 = std::tan(1.5707964f * float(freq_norm_));
		float fSlow1 = fSlow0 + 1.0f;
		float fSlow2 = fSlow0 / fSlow1;
		float fSlow3 = 24.293f * float(res_) + -0.00010678119f;
		float fSlow4 = 0.1646572f * fSlow3 * (1.0f - fSlow2);
		float fSlow5 = 1.0f / (0.1646572f * (ladder_faustpower4_f(fSlow0) * fSlow3 / ladder_faustpower4_f(fSlow1)) + 1.0f);
		float fSlow6 = 2.0f * fSlow2;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = fSlow5 * (float(input0[i0]) + float(input1[i0]) - fSlow4 * (fRec3[1] + fSlow2 * (fRec2[1] + fSlow2 * (fRec1[1] + fSlow2 * fRec0[1])))) - fRec0[1];
			fRec0[0] = fRec0[1] + fSlow6 * fTemp0;
			float fTemp1 = fRec0[1] + fSlow2 * fTemp0 - fRec1[1];
			fRec1[0] = fRec1[1] + fSlow6 * fTemp1;
			float fTemp2 = fRec1[1] + fSlow2 * fTemp1 - fRec2[1];
			fRec2[0] = fRec2[1] + fSlow6 * fTemp2;
			float fTemp3 = fRec2[1] + fSlow2 * fTemp2 - fRec3[1];
			fRec3[0] = fRec3[1] + fSlow6 * fTemp3;
			float fRec4 = fRec3[1] + fSlow2 * fTemp3;
			float fTemp4 = 0.5f * fRec4;
			output0[i0] = float(fTemp4);
			output1[i0] = float(fTemp4);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
		}
	}

};
