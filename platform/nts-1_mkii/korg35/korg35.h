/* ------------------------------------------------------------
name: "korg35"
Code generated with Faust 2.72.14 (https://faust.grame.fr)
Compilation options: -lang cpp -nvi -ct 1 -cn korg35 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */


#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS korg35
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


class korg35 {
	
 private:
	
	float mode_;
	float freq_norm_;
	float res_;

	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec4[2];
	float fConst3;
	float fRec5[2];
	float fRec0[2];
	float fRec1[2];
	float fRec2[2];
	float fRec10[2];
	float fRec11[2];
	float fRec12[2];
	float fRec6[2];
	float fRec7[2];
	float fRec8[2];
	float fRec14[2];
	float fRec15[2];
	float fRec16[2];
	
 public:
	korg35() {}

	enum FilterMode {
		LP = 0,
		BP,
		HP,
		NUM_MODE
	};

	void setFreqNormalized(float freq)
	{
		freq_norm_ = freq;
	}

	void setResonance(float res)
	{
		res_ = res;
	}

	void setMode(FilterMode mode)
	{
		mode_ = mode;
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
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 6.2831855f / fConst0;
	}
	
	void instanceResetUserInterface() {
		mode_ = float(0.0f);
		freq_norm_ = float(1.0f);
		res_ = float(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec4[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec10[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec11[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec12[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec6[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec7[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec14[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec15[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec16[l13] = 0.0f;
		}
	}
	
	void init(int sample_rate) {
		classInit(sample_rate);
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
	// 	ui_interface->openVerticalBox("korg35");
	// 	ui_interface->declare(&mode_, "0", "");
	// 	ui_interface->addHorizontalSlider("mode", &mode_, float(0.0f), float(0.0f), float(2.0f), float(1.0f));
	// 	ui_interface->declare(&freq_norm_, "1", "");
	// 	ui_interface->addHorizontalSlider("freq", &freq_norm_, float(1.0f), float(0.0f), float(1.0f), float(0.001f));
	// 	ui_interface->declare(&res_, "2", "");
	// 	ui_interface->addHorizontalSlider("resonance", &res_, float(0.0f), float(0.0f), float(1.0f), float(0.001f));
	// 	ui_interface->closeBox();
	// }
	
	void compute(int count, float** RESTRICT inputs, float** RESTRICT outputs) {
		float* input0 = inputs[0];
		float* input1 = inputs[1];
		float* output0 = outputs[0];
		float* output1 = outputs[1];
		bool iSlow1 = mode_ >= 2;
		bool iSlow2 = mode_ >= 1;
		float fSlow3 = fConst1 * float(freq_norm_);
		float fSlow4 = fConst1 * (9.2f * float(res_) + 0.5f);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec4[0] = fSlow3 + fConst2 * fRec4[1];
			float fTemp0 = std::tan(fConst3 * std::pow(1e+01f, 3.0f * fRec4[0] + 1.0f));
			float fTemp1 = fTemp0 + 1.0f;
			float fTemp2 = 1.0f - fTemp0 / fTemp1;
			fRec5[0] = fSlow4 + fConst2 * fRec5[1];
			float fTemp3 = fRec5[0] + -0.70710677f;
			float fTemp4 = 1.0f - 0.21521823f * (fTemp0 * fTemp3 * fTemp2 / fTemp1);
			float fTemp5 = float(input0[i0]) + float(input1[i0]);
			float fTemp6 = (fTemp5 - fRec2[1]) * fTemp0;
			float fTemp7 = fTemp0 * ((fRec2[1] - (fRec0[1] - (fTemp6 + 0.21521823f * fRec1[1] * fTemp3 * fTemp2)) / fTemp1) / fTemp4 - fRec1[1]) / fTemp1;
			float fTemp8 = fRec1[1] + fTemp7;
			fRec0[0] = fRec0[1] + 2.0f * (fTemp0 * (0.21521823f * fTemp3 * fTemp8 - fRec0[1]) / fTemp1);
			fRec1[0] = fRec1[1] + 2.0f * fTemp7;
			fRec2[0] = fRec2[1] + 2.0f * (fTemp6 / fTemp1);
			float fRec3 = fTemp8;
			float fTemp9 = 0.5f * (0.1f - 0.05f * fRec4[0]);
			float fTemp10 = std::tan(fConst3 * std::pow(1e+01f, 3.0f * std::min<float>(fRec4[0] + fTemp9, 1.0f) + 1.0f));
			float fTemp11 = fTemp10 + 1.0f;
			float fTemp12 = 1.0f - fTemp10 / fTemp11;
			float fTemp13 = std::tan(fConst3 * std::pow(1e+01f, 3.0f * std::max<float>(fRec4[0] - fTemp9, 0.0f) + 1.0f));
			float fTemp14 = fTemp13 + 1.0f;
			float fTemp15 = 0.21521823f * (fTemp3 * fTemp13 * (fTemp13 / fTemp14 + -1.0f) / fTemp14) + 1.0f;
			float fTemp16 = (fTemp5 - fRec12[1]) * fTemp13;
			float fTemp17 = fTemp5 - (fRec12[1] + (fTemp16 - fRec11[1] + fTemp13 * fRec10[1] / fTemp14) / fTemp14);
			float fTemp18 = 0.21521823f * (fTemp3 * fTemp17 / fTemp15);
			float fTemp19 = fTemp13 * (fTemp18 - fRec10[1]) / fTemp14;
			fRec10[0] = fRec10[1] + 2.0f * fTemp19;
			fRec11[0] = fRec11[1] + 2.0f * (fTemp13 * (fTemp18 - (fRec10[1] + fRec11[1] + fTemp19)) / fTemp14);
			fRec12[0] = fRec12[1] + 2.0f * (fTemp16 / fTemp14);
			float fRec13 = fTemp17 / fTemp15;
			float fTemp20 = (fRec13 - fRec8[1]) * fTemp10;
			float fTemp21 = fTemp10 * ((fRec8[1] + (fTemp20 + 0.21521823f * fTemp3 * fRec7[1] * fTemp12 - fRec6[1]) / fTemp11) / (1.0f - 0.21521823f * (fTemp3 * fTemp10 * fTemp12 / fTemp11)) - fRec7[1]) / fTemp11;
			float fTemp22 = fRec7[1] + fTemp21;
			fRec6[0] = fRec6[1] + 2.0f * (fTemp10 * (0.21521823f * fTemp3 * fTemp22 - fRec6[1]) / fTemp11);
			fRec7[0] = fRec7[1] + 2.0f * fTemp21;
			fRec8[0] = fRec8[1] + 2.0f * (fTemp20 / fTemp11);
			float fRec9 = fTemp22;
			float fTemp23 = fTemp0 * (fTemp5 - fRec16[1]);
			float fTemp24 = fTemp5 + (fRec15[1] - fTemp23 - fTemp0 * fRec14[1] / fTemp1) / fTemp1 - fRec16[1];
			float fTemp25 = 0.21521823f * (fTemp3 * fTemp24 / fTemp4);
			float fTemp26 = fTemp0 * (fTemp25 - fRec14[1]) / fTemp1;
			fRec14[0] = fRec14[1] + 2.0f * fTemp26;
			fRec15[0] = fRec15[1] + 2.0f * (fTemp0 * (fTemp25 - (fTemp26 + fRec15[1] + fRec14[1])) / fTemp1);
			fRec16[0] = fRec16[1] + 2.0f * (fTemp23 / fTemp1);
			float fRec17 = fTemp24 / fTemp4;
			float fTemp27 = 0.5f * ((iSlow1) ? fRec17 : ((iSlow2) ? fRec9 : fRec3));
			output0[i0] = float(fTemp27);
			output1[i0] = float(fTemp27);
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
		}
	}

};