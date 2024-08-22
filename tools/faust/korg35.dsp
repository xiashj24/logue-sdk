import("stdfaust.lib");
mode = hslider("[0]mode", 0, 0, 3, 1);
normFreq = hslider("[1]freq",1,0,1,0.0001) : si.smoo;
resonance = hslider("[2]resonance", 0, 0, 1, 0.0001) : si.smoo;

Q_korg = resonance , 0.5, 10 : it.interpolate_linear;
// freq(n) = 2*(10^(3*n+1));

f2_1 = normFreq, 0.7869762832625042, 0.507155667499064 : it.interpolate_linear;
f2_2 = normFreq, 0.48899786615997504, 0.6235193962753848 : it.interpolate_linear;

clip = aa.hardclip2;
post_gain = it.interpolate_linear(aa.cubic1(resonance) * 1.5, 1, 2/3);
// post_gain = 1;

korg_lpf = ve.korg35LPF(normFreq,Q_korg) : clip : _*post_gain;
korg_hpf = ve.korg35HPF(normFreq,Q_korg) : clip : _*post_gain;
// lpf1 = ve.moog_vcf_2bn(resonance*0.99, freq(f2_1));
// lpf2 = ve.moog_vcf_2bn(resonance*0.99, freq(f2_2));
lpf1 = ve.korg35LPF(f2_1,Q_korg-0.2) : clip : _*post_gain;
lpf2 = ve.korg35LPF(f2_2,Q_korg-0.2) : clip : _*post_gain;
// bpf = korg_hpf:korg_lpf; // too much distortion
formant1 = korg_hpf : lpf1;
formant2 = korg_hpf : lpf2;
filter = _<:_,_,_,_ : korg_lpf, korg_hpf, formant1, formant2: ba.selectn(4, mode);

decimation_filter = fi.lowpass(4, 20000);
// decimation_filter = _;

process = _,_ :> _*0.5 : filter : decimation_filter <: _,_;
// osc_freq = hslider("[3]osc freq", 100, 50, 1000, 0.1);
// inputSignal = os.sawtooth(osc_freq); 
// process = inputSignal : filter <: _,_; 
