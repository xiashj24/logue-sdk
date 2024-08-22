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

static float korg35_faustpower2_f(float value) {
	return value * value;
}
static float korg35_faustpower4_f(float value) {
	return value * value * value * value;
}
static float korg35_faustpower3_f(float value) {
	return value * value * value;
}

class korg35  {
	
 private:
	FAUSTFLOAT mode_;
	FAUSTFLOAT res_;
	FAUSTFLOAT freq_;
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fRec2[2];
	float fRec7[2];
	float fConst11;
	float fRec3[2];
	float fRec4[2];
	float fRec5[2];
	float fRec6[3];
	float fRec8[2];
	float fRec9[2];
	float fRec10[2];
	float fRec11[3];
	float fRec12[2];
	float fRec13[2];
	float fRec14[2];
	float fRec15[3];
	float fRec16[2];
	float fRec17[2];
	float fRec18[2];
	float fRec19[3];
	float fRec1[3];
	float fRec0[3];
	
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
		fConst1 = std::tan(62831.85f / fConst0);
		fConst2 = 2.0f * (1.0f - 1.0f / korg35_faustpower2_f(fConst1));
		fConst3 = 1.0f / fConst1;
		fConst4 = (fConst3 + -0.76536685f) / fConst1 + 1.0f;
		fConst5 = 1.0f / ((fConst3 + 0.76536685f) / fConst1 + 1.0f);
		fConst6 = (fConst3 + -1.847759f) / fConst1 + 1.0f;
		fConst7 = 1.0f / ((fConst3 + 1.847759f) / fConst1 + 1.0f);
		fConst8 = 1.0f / fConst0;
		fConst9 = 44.1f / fConst0;
		fConst10 = 1.0f - fConst9;
		fConst11 = 6.2831855f / fConst0;
	}
	
	void instanceResetUserInterface() {
		mode_ = FAUSTFLOAT(0.0f);
		res_ = FAUSTFLOAT(0.0f);
		freq_ = FAUSTFLOAT(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec7[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec8[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec9[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec10[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec11[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec12[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec13[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec14[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec15[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec16[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec17[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec18[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec19[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec1[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec0[l19] = 0.0f;
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
		float fSlow3 = fConst9 * float(res_);
		float fSlow4 = fConst9 * float(freq_);
		int iSlow5 = fSlow0 >= 3.0f;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec2[0] = fSlow3 + fConst10 * fRec2[1];
			float fTemp0 = fRec2[0] - fRec2[1];
			float fTemp1 = 0.6666667f * fRec2[1];
			float fTemp2 = 0.6666667f * fRec2[0];
			float fTemp3 = 0.5f * (fRec2[0] + fRec2[1]);
			float fTemp4 = 1.0f - 0.5f * ((std::fabs(fTemp0) <= fConst8) ? (((fTemp3 < 1.0f) & (fTemp3 > -1.0f)) ? fTemp3 - 0.33333334f * korg35_faustpower3_f(fTemp3) : 0.6666667f * float((fTemp3 > 0.0f) - (fTemp3 < 0.0f))) : (((fRec2[0] <= -1.0f) ? -fTemp2 : ((fRec2[0] >= 1.0f) ? fTemp2 : 0.5f * korg35_faustpower2_f(fRec2[0]) - 0.083333336f * korg35_faustpower4_f(fRec2[0]))) - ((fRec2[1] <= -1.0f) ? -fTemp1 : ((fRec2[1] >= 1.0f) ? fTemp1 : 0.5f * korg35_faustpower2_f(fRec2[1]) - 0.083333336f * korg35_faustpower4_f(fRec2[1])))) / fTemp0);
			fRec7[0] = fSlow4 + fConst10 * fRec7[1];
			float fTemp5 = std::tan(fConst11 * std::pow(1e+01f, 3.0f * fRec7[0] + 1.0f));
			float fTemp6 = fTemp5 + 1.0f;
			float fTemp7 = 0.5f * (float(input0[i0]) + float(input1[i0]));
			float fTemp8 = (fTemp7 - fRec3[1]) * fTemp5;
			fRec3[0] = fRec3[1] + 2.0f * (fTemp8 / fTemp6);
			float fTemp9 = fTemp5 / fTemp6;
			float fTemp10 = 9.5f * fRec2[0];
			float fTemp11 = fTemp10 + -0.20710678f;
			float fTemp12 = 1.0f - 0.21521823f * (fTemp5 * fTemp11 * (1.0f - fTemp9) / fTemp6);
			float fTemp13 = fTemp5 * ((fRec3[1] + (fTemp8 - 0.21521823f * fRec4[1] * fTemp11 * (fTemp9 + -1.0f) - fRec5[1]) / fTemp6) / fTemp12 - fRec4[1]) / fTemp6;
			fRec4[0] = fRec4[1] + 2.0f * fTemp13;
			float fTemp14 = fRec4[1] + fTemp13;
			fRec5[0] = fRec5[1] + 2.0f * (fTemp5 * (0.21521823f * fTemp11 * fTemp14 - fRec5[1]) / fTemp6);
			fRec6[0] = fTemp14;
			int iTemp15 = (fRec6[2] <= 1.0f) & (fRec6[2] >= -1.0f);
			float fTemp16 = 0.5f * korg35_faustpower2_f(fRec6[2]);
			float fTemp17 = float((fRec6[2] > 0.0f) - (fRec6[2] < 0.0f));
			int iTemp18 = (fRec6[1] <= 1.0f) & (fRec6[1] >= -1.0f);
			float fTemp19 = float((fRec6[1] > 0.0f) - (fRec6[1] < 0.0f));
			float fTemp20 = 0.5f * korg35_faustpower2_f(fRec6[1]);
			float fTemp21 = ((iTemp18) ? fTemp20 : fRec6[1] * fTemp19 + -0.5f);
			float fTemp22 = ((iTemp18) ? 0.33333334f * korg35_faustpower3_f(fRec6[1]) : fTemp19 * (fTemp20 + -0.16666667f));
			float fTemp23 = 2.0f * fRec6[1];
			float fTemp24 = korg35_faustpower2_f(fRec6[0] - fRec6[1]);
			int iTemp25 = (fRec6[0] <= 1.0f) & (fRec6[0] >= -1.0f);
			float fTemp26 = 0.5f * korg35_faustpower2_f(fRec6[0]);
			float fTemp27 = float((fRec6[0] > 0.0f) - (fRec6[0] < 0.0f));
			float fTemp28 = fTemp5 * (fTemp7 - fRec8[1]);
			fRec8[0] = fRec8[1] + 2.0f * (fTemp28 / fTemp6);
			float fTemp29 = fTemp7 - (fRec8[1] + (fTemp28 - fRec9[1] + fTemp5 * fRec10[1] / fTemp6) / fTemp6);
			float fTemp30 = 0.21521823f * (fTemp11 * fTemp29 / fTemp12);
			float fTemp31 = fTemp5 * (fTemp30 - fRec10[1]) / fTemp6;
			fRec9[0] = fRec9[1] + 2.0f * (fTemp5 * (fTemp30 - (fRec10[1] + fRec9[1] + fTemp31)) / fTemp6);
			fRec10[0] = fRec10[1] + 2.0f * fTemp31;
			fRec11[0] = fTemp29 / fTemp12;
			int iTemp32 = (fRec11[2] <= 1.0f) & (fRec11[2] >= -1.0f);
			float fTemp33 = 0.5f * korg35_faustpower2_f(fRec11[2]);
			float fTemp34 = float((fRec11[2] > 0.0f) - (fRec11[2] < 0.0f));
			int iTemp35 = (fRec11[1] <= 1.0f) & (fRec11[1] >= -1.0f);
			float fTemp36 = float((fRec11[1] > 0.0f) - (fRec11[1] < 0.0f));
			float fTemp37 = 0.5f * korg35_faustpower2_f(fRec11[1]);
			float fTemp38 = ((iTemp35) ? fTemp37 : fRec11[1] * fTemp36 + -0.5f);
			float fTemp39 = ((iTemp35) ? 0.33333334f * korg35_faustpower3_f(fRec11[1]) : fTemp36 * (fTemp37 + -0.16666667f));
			float fTemp40 = 2.0f * fRec11[1];
			float fTemp41 = korg35_faustpower2_f(fRec11[0] - fRec11[1]);
			int iTemp42 = (fRec11[0] <= 1.0f) & (fRec11[0] >= -1.0f);
			float fTemp43 = 0.5f * korg35_faustpower2_f(fRec11[0]);
			float fTemp44 = float((fRec11[0] > 0.0f) - (fRec11[0] < 0.0f));
			float fTemp45 = fTemp4 * (((fTemp41 <= fConst8) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fRec11[0] + fTemp40))) : (fRec11[0] * (((iTemp42) ? fTemp43 : fRec11[0] * fTemp44 + -0.5f) - fTemp38) + fTemp39 - ((iTemp42) ? 0.33333334f * korg35_faustpower3_f(fRec11[0]) : fTemp44 * (fTemp43 + -0.16666667f))) / fTemp41) + ((korg35_faustpower2_f(fRec11[1] - fRec11[2]) <= fConst8) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fTemp40 + fRec11[2]))) : (fTemp39 + fRec11[2] * (((iTemp32) ? fTemp33 : fRec11[2] * fTemp34 + -0.5f) - fTemp38) - ((iTemp32) ? 0.33333334f * korg35_faustpower3_f(fRec11[2]) : fTemp34 * (fTemp33 + -0.16666667f))) / korg35_faustpower2_f(fRec11[2] - fRec11[1])));
			float fTemp46 = std::tan(fConst11 * std::pow(1e+01f, 3.0f * (0.7869763f - 0.27982062f * fRec7[0]) + 1.0f));
			float fTemp47 = fTemp46 + 1.0f;
			float fTemp48 = (fTemp45 - fRec12[1]) * fTemp46;
			fRec12[0] = fRec12[1] + 2.0f * (fTemp48 / fTemp47);
			float fTemp49 = fTemp46 / fTemp47;
			float fTemp50 = fTemp10 + -0.5071068f;
			float fTemp51 = fTemp46 * ((fRec12[1] + (fTemp48 - 0.21521823f * fRec13[1] * fTemp50 * (fTemp49 + -1.0f) - fRec14[1]) / fTemp47) / (1.0f - 0.21521823f * (fTemp46 * fTemp50 * (1.0f - fTemp49) / fTemp47)) - fRec13[1]) / fTemp47;
			fRec13[0] = fRec13[1] + 2.0f * fTemp51;
			float fTemp52 = fRec13[1] + fTemp51;
			fRec14[0] = fRec14[1] + 2.0f * (fTemp46 * (0.21521823f * fTemp50 * fTemp52 - fRec14[1]) / fTemp47);
			fRec15[0] = fTemp52;
			int iTemp53 = (fRec15[2] <= 1.0f) & (fRec15[2] >= -1.0f);
			float fTemp54 = 0.5f * korg35_faustpower2_f(fRec15[2]);
			float fTemp55 = float((fRec15[2] > 0.0f) - (fRec15[2] < 0.0f));
			int iTemp56 = (fRec15[1] <= 1.0f) & (fRec15[1] >= -1.0f);
			float fTemp57 = float((fRec15[1] > 0.0f) - (fRec15[1] < 0.0f));
			float fTemp58 = 0.5f * korg35_faustpower2_f(fRec15[1]);
			float fTemp59 = ((iTemp56) ? fTemp58 : fRec15[1] * fTemp57 + -0.5f);
			float fTemp60 = ((iTemp56) ? 0.33333334f * korg35_faustpower3_f(fRec15[1]) : fTemp57 * (fTemp58 + -0.16666667f));
			float fTemp61 = 2.0f * fRec15[1];
			float fTemp62 = korg35_faustpower2_f(fRec15[0] - fRec15[1]);
			int iTemp63 = (fRec15[0] <= 1.0f) & (fRec15[0] >= -1.0f);
			float fTemp64 = 0.5f * korg35_faustpower2_f(fRec15[0]);
			float fTemp65 = float((fRec15[0] > 0.0f) - (fRec15[0] < 0.0f));
			float fTemp66 = std::tan(fConst11 * std::pow(1e+01f, 3.0f * (0.13452153f * fRec7[0] + 0.48899788f) + 1.0f));
			float fTemp67 = fTemp66 + 1.0f;
			float fTemp68 = (fTemp45 - fRec16[1]) * fTemp66;
			fRec16[0] = fRec16[1] + 2.0f * (fTemp68 / fTemp67);
			float fTemp69 = 1.0f - fTemp66 / fTemp67;
			float fTemp70 = fTemp66 * ((fRec16[1] - (fRec18[1] - (fTemp68 + 0.21521823f * fTemp50 * fRec17[1] * fTemp69)) / fTemp67) / (1.0f - 0.21521823f * (fTemp50 * fTemp66 * fTemp69 / fTemp67)) - fRec17[1]) / fTemp67;
			fRec17[0] = fRec17[1] + 2.0f * fTemp70;
			float fTemp71 = fRec17[1] + fTemp70;
			fRec18[0] = fRec18[1] + 2.0f * (fTemp66 * (0.21521823f * fTemp50 * fTemp71 - fRec18[1]) / fTemp67);
			fRec19[0] = fTemp71;
			int iTemp72 = (fRec19[2] <= 1.0f) & (fRec19[2] >= -1.0f);
			float fTemp73 = 0.5f * korg35_faustpower2_f(fRec19[2]);
			float fTemp74 = float((fRec19[2] > 0.0f) - (fRec19[2] < 0.0f));
			int iTemp75 = (fRec19[1] <= 1.0f) & (fRec19[1] >= -1.0f);
			float fTemp76 = float((fRec19[1] > 0.0f) - (fRec19[1] < 0.0f));
			float fTemp77 = 0.5f * korg35_faustpower2_f(fRec19[1]);
			float fTemp78 = ((iTemp75) ? fTemp77 : fRec19[1] * fTemp76 + -0.5f);
			float fTemp79 = ((iTemp75) ? 0.33333334f * korg35_faustpower3_f(fRec19[1]) : fTemp76 * (fTemp77 + -0.16666667f));
			float fTemp80 = 2.0f * fRec19[1];
			float fTemp81 = korg35_faustpower2_f(fRec19[0] - fRec19[1]);
			int iTemp82 = (fRec19[0] <= 1.0f) & (fRec19[0] >= -1.0f);
			float fTemp83 = 0.5f * korg35_faustpower2_f(fRec19[0]);
			float fTemp84 = float((fRec19[0] > 0.0f) - (fRec19[0] < 0.0f));
			fRec1[0] = ((iSlow1) ? ((iSlow5) ? fTemp4 * (((fTemp81 <= fConst8) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fRec19[0] + fTemp80))) : (fRec19[0] * (((iTemp82) ? fTemp83 : fRec19[0] * fTemp84 + -0.5f) - fTemp78) + fTemp79 - ((iTemp82) ? 0.33333334f * korg35_faustpower3_f(fRec19[0]) : fTemp84 * (fTemp83 + -0.16666667f))) / fTemp81) + ((korg35_faustpower2_f(fRec19[1] - fRec19[2]) <= fConst8) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fTemp80 + fRec19[2]))) : (fTemp79 + fRec19[2] * (((iTemp72) ? fTemp73 : fRec19[2] * fTemp74 + -0.5f) - fTemp78) - ((iTemp72) ? 0.33333334f * korg35_faustpower3_f(fRec19[2]) : fTemp74 * (fTemp73 + -0.16666667f))) / korg35_faustpower2_f(fRec19[2] - fRec19[1]))) : fTemp4 * (((fTemp62 <= fConst8) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fRec15[0] + fTemp61))) : (fRec15[0] * (((iTemp63) ? fTemp64 : fRec15[0] * fTemp65 + -0.5f) - fTemp59) + fTemp60 - ((iTemp63) ? 0.33333334f * korg35_faustpower3_f(fRec15[0]) : fTemp65 * (fTemp64 + -0.16666667f))) / fTemp62) + ((korg35_faustpower2_f(fRec15[1] - fRec15[2]) <= fConst8) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fTemp61 + fRec15[2]))) : (fTemp60 + fRec15[2] * (((iTemp53) ? fTemp54 : fRec15[2] * fTemp55 + -0.5f) - fTemp59) - ((iTemp53) ? 0.33333334f * korg35_faustpower3_f(fRec15[2]) : fTemp55 * (fTemp54 + -0.16666667f))) / korg35_faustpower2_f(fRec15[2] - fRec15[1])))) : ((iSlow2) ? fTemp45 : (((fTemp24 <= fConst8) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fRec6[0] + fTemp23))) : (fRec6[0] * (((iTemp25) ? fTemp26 : fRec6[0] * fTemp27 + -0.5f) - fTemp21) + fTemp22 - ((iTemp25) ? 0.33333334f * korg35_faustpower3_f(fRec6[0]) : fTemp27 * (fTemp26 + -0.16666667f))) / fTemp24) + ((korg35_faustpower2_f(fRec6[1] - fRec6[2]) <= fConst8) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fTemp23 + fRec6[2]))) : (fTemp22 + fRec6[2] * (((iTemp15) ? fTemp16 : fRec6[2] * fTemp17 + -0.5f) - fTemp21) - ((iTemp15) ? 0.33333334f * korg35_faustpower3_f(fRec6[2]) : fTemp17 * (fTemp16 + -0.16666667f))) / korg35_faustpower2_f(fRec6[2] - fRec6[1]))) * fTemp4)) - fConst7 * (fConst6 * fRec1[2] + fConst2 * fRec1[1]);
			fRec0[0] = fConst7 * (fRec1[2] + fRec1[0] + 2.0f * fRec1[1]) - fConst5 * (fConst4 * fRec0[2] + fConst2 * fRec0[1]);
			float fTemp85 = fConst5 * (fRec0[2] + fRec0[0] + 2.0f * fRec0[1]);
			output0[i0] = FAUSTFLOAT(fTemp85);
			output1[i0] = FAUSTFLOAT(fTemp85);
			fRec2[1] = fRec2[0];
			fRec7[1] = fRec7[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
		}
	}

};

#endif
