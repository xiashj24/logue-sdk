/* ------------------------------------------------------------
name: "korg35"
Code generated with Faust 2.74.6 (https://faust.grame.fr)
Compilation options: -lang cpp -nvi -ct 1 -cn korg35 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __korg35_H__
#define  __korg35_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
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


class korg35  {
	
 private:
	FAUSTFLOAT mode_;
	FAUSTFLOAT res_;
	FAUSTFLOAT freq_;
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec4[2];
	float fRec5[2];
	float fConst3;
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec7[2];
	float fRec8[2];
	float fRec9[2];
	float fRec11[2];
	float fRec12[2];
	float fRec13[2];
	float fRec15[2];
	float fRec16[2];
	float fRec17[2];
	
 public:
	korg35() {
	}
	
	enum FilterMode {
		LP = 0,
		HP,
		FORMANT1,
		FORMANT2,
		NUM_MODE
	};

	void setFreqNormalized(float freq)
	{
		freq_ = freq;
	}

	void setResonance(float res)
	{
		res_ = res;
	}

	void setMode(int mode)
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
		mode_ = FAUSTFLOAT(0.0f);
		res_ = FAUSTFLOAT(0.0f);
		freq_ = FAUSTFLOAT(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec4[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec3[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec7[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec8[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec9[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec11[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec12[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec13[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec15[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec16[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec17[l13] = 0.0f;
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
	
	korg35* clone() {
		return new korg35();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	/* void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("korg35");
		ui_interface->declare(&mode_, "0", "");
		ui_interface->addHorizontalSlider("mode", &mode_, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&freq_, "1", "");
		ui_interface->addHorizontalSlider("freq", &freq_, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0001f));
		ui_interface->declare(&res_, "2", "");
		ui_interface->addHorizontalSlider("resonance", &res_, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0001f));
		ui_interface->closeBox();
	} */
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(mode_);
		int iSlow1 = fSlow0 >= 2.0f;
		int iSlow2 = fSlow0 >= 1.0f;
		float fSlow3 = fConst1 * float(res_);
		float fSlow4 = fConst1 * float(freq_);
		int iSlow5 = fSlow0 >= 3.0f;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec4[0] = fSlow3 + fConst2 * fRec4[1];
			float fTemp0 = 8.4928f * fRec4[0];
			float fTemp1 = fTemp0 + 9.321881e-05f;
			fRec5[0] = fSlow4 + fConst2 * fRec5[1];
			float fTemp2 = std::tan(fConst3 * std::pow(1e+01f, 3.0f * fRec5[0] + 1.0f));
			float fTemp3 = fTemp2 + 1.0f;
			float fTemp4 = 1.0f - fTemp2 / fTemp3;
			float fTemp5 = 1.0f - 0.21521823f * (fTemp2 * fTemp1 * fTemp4 / fTemp3);
			float fTemp6 = 0.5f * (float(input0[i0]) + float(input1[i0]));
			float fTemp7 = (fTemp6 - fRec3[1]) * fTemp2;
			float fTemp8 = fTemp2 * ((fRec3[1] + (fTemp7 + 0.21521823f * fRec1[1] * fTemp1 * fTemp4 - fRec2[1]) / fTemp3) / fTemp5 - fRec1[1]) / fTemp3;
			float fTemp9 = tanhf(0.107609116f * fTemp1 * (fRec1[1] + fTemp8));
			float fRec0 = 9.292893f * (fTemp9 / fTemp1);
			fRec1[0] = fRec1[1] + 2.0f * fTemp8;
			fRec2[0] = fRec2[1] + 2.0f * (fTemp2 * (2.0f * fTemp9 - fRec2[1]) / fTemp3);
			fRec3[0] = fRec3[1] + 2.0f * (fTemp7 / fTemp3);
			float fTemp10 = fTemp2 * (fTemp6 - fRec9[1]);
			float fTemp11 = tanhf(0.107609116f * (fTemp1 * (fTemp6 - (fRec9[1] + (fTemp10 - fRec7[1] + fTemp2 * fRec8[1] / fTemp3) / fTemp3)) / fTemp5));
			float fRec6 = 9.292893f * (fTemp11 / fTemp1);
			float fTemp12 = 2.0f * fTemp11;
			float fTemp13 = fTemp2 * (fTemp12 - fRec8[1]) / fTemp3;
			fRec7[0] = fRec7[1] + 2.0f * (fTemp2 * (fTemp12 - (fTemp13 + fRec7[1] + fRec8[1])) / fTemp3);
			fRec8[0] = fRec8[1] + 2.0f * fTemp13;
			fRec9[0] = fRec9[1] + 2.0f * (fTemp10 / fTemp3);
			float fTemp14 = fTemp0 + -0.19990678f;
			float fTemp15 = std::tan(fConst3 * std::pow(1e+01f, 3.0f * (0.7869763f - 0.27982062f * fRec5[0]) + 1.0f));
			float fTemp16 = fTemp15 + 1.0f;
			float fTemp17 = 1.0f - fTemp15 / fTemp16;
			float fTemp18 = (fRec6 - fRec13[1]) * fTemp15;
			float fTemp19 = fTemp15 * ((fRec13[1] - (fRec12[1] - (fTemp18 + 0.21521823f * fRec11[1] * fTemp14 * fTemp17)) / fTemp16) / (1.0f - 0.21521823f * (fTemp15 * fTemp14 * fTemp17 / fTemp16)) - fRec11[1]) / fTemp16;
			float fTemp20 = tanhf(0.107609116f * fTemp14 * (fRec11[1] + fTemp19));
			float fRec10 = 9.292893f * (fTemp20 / fTemp14);
			fRec11[0] = fRec11[1] + 2.0f * fTemp19;
			fRec12[0] = fRec12[1] + 2.0f * (fTemp15 * (2.0f * fTemp20 - fRec12[1]) / fTemp16);
			fRec13[0] = fRec13[1] + 2.0f * (fTemp18 / fTemp16);
			float fTemp21 = std::tan(fConst3 * std::pow(1e+01f, 3.0f * (0.13452153f * fRec5[0] + 0.48899788f) + 1.0f));
			float fTemp22 = fTemp21 + 1.0f;
			float fTemp23 = 1.0f - fTemp21 / fTemp22;
			float fTemp24 = (fRec6 - fRec17[1]) * fTemp21;
			float fTemp25 = fTemp21 * ((fRec17[1] - (fRec16[1] - (fTemp24 + 0.21521823f * fTemp14 * fRec15[1] * fTemp23)) / fTemp22) / (1.0f - 0.21521823f * (fTemp14 * fTemp21 * fTemp23 / fTemp22)) - fRec15[1]) / fTemp22;
			float fTemp26 = tanhf(0.107609116f * fTemp14 * (fRec15[1] + fTemp25));
			float fRec14 = 9.292893f * (fTemp26 / fTemp14);
			fRec15[0] = fRec15[1] + 2.0f * fTemp25;
			fRec16[0] = fRec16[1] + 2.0f * (fTemp21 * (2.0f * fTemp26 - fRec16[1]) / fTemp22);
			fRec17[0] = fRec17[1] + 2.0f * (fTemp24 / fTemp22);
			float fTemp27 = ((iSlow1) ? ((iSlow5) ? fRec14 : fRec10) : ((iSlow2) ? fRec6 : fRec0));
			output0[i0] = FAUSTFLOAT(fTemp27);
			output1[i0] = FAUSTFLOAT(fTemp27);
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
		}
	}

};

#endif
