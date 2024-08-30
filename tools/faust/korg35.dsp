import("stdfaust.lib");
mode = hslider("[0]mode", 0, 0, 3, 1);
normFreq = hslider("[1]freq",1,0,1,0.0001) : si.smoo;
resonance = hslider("[2]resonance", 0, 0, 1, 0.0001) : si.smoo;

Q_korg = resonance , 0.7072, 9.2 : it.interpolate_linear;
// freq(n) = 2*(10^(3*n+1))
lv = 2;
NLP = *(1/lv):ma.tanh:_*lv;

f2_1 = normFreq, 0.7869762832625042, 0.507155667499064 : it.interpolate_linear;
f2_2 = normFreq, 0.48899786615997504, 0.6235193962753848 : it.interpolate_linear;
korg35LPF(normFreq,Q) = _ <: (s1,s2,s3,y) : !,!,!,_
letrec{
  's1 = _-s1:_*(alpha*2):_+s1;
  's2 = _-s1:_*alpha:_+s1:_+(s3*B3):_+(s2*B2):_*alpha0:_-s3:_*alpha:_+s3:_*K:NLP:_-s2:_*(alpha*2):_+s2;
  's3 = _-s1:_*alpha:_+s1:_+(s3*B3):_+(s2*B2):_*alpha0:_-s3:_*(alpha*2):_+s3;
  'y = _-s1:_*alpha:_+s1:_+(s3*B3):_+(s2*B2) :_*alpha0:_-s3:_*alpha:_+s3:_*K:NLP:_*(1/K);
}
with{
  invSqrt2 = 1/sqrt(2);
  freq = 2*(10^(3*normFreq+1));
  K = 2.0*(Q - invSqrt2)/(10.0 - invSqrt2);
  wd = 2*ma.PI*freq;
  T = 1/ma.SR;
  wa = (2/T)*tan(wd*T/2); // freq pre-warp
  g = wa*T/2; 
  G = g/(1.0 + g);
  alpha = G;
  B3 = (K - K*G)/(1 + g);
  B2 = -1/(1 + g);
  alpha0 = 1/(1 - K*G + K*G*G); 
};

korg35HPF(normFreq,Q) = _ <: (s1,s2,s3,y) : !,!,!,_
letrec{
  's1 = _-s1:_*(alpha*2):_+s1;
  's2 = _<:(_-s1:_*alpha:_+s1)*-1,_:>_+(s3*B3):_+(s2*B2):_*alpha0:_*K:NLP:_-s2:_*alpha*2:_+s2;
  's3 = _<:(_-s1:_*alpha:_+s1)*-1,_:>_+(s3*B3):_+(s2*B2):_*alpha0:_*K:NLP:_<:(_-s2:_*alpha:_+s2)*-1,_:>_-s3:_*alpha*2:_+s3;
  'y = _<:(_-s1:_*alpha:_+s1)*-1,_:>_+(s3*B3):_+(s2*B2):_*alpha0:_*K:NLP:_*(1/K);
}
with{
  invSqrt2 = 1/sqrt(2);
  freq = 2*(10^(3*normFreq+1));
  K = 2.0*(Q - invSqrt2)/(10.0 - invSqrt2);
  wd = 2*ma.PI*freq;
  T = 1/ma.SR;
  wa = (2/T)*tan(wd*T/2);
  g = wa*T/2; 
  G = g/(1.0 + g);
  alpha = G;
  B3 = 1.0/(1.0 + g);
  B2 = -1.0*G/(1.0 + g);
  alpha0 = 1/(1 - K*G + K*G*G);
};

// clip = _;
// clip = aa.hardclip2;
// lv = 3;
// clip = _*(1/lv):aa.hardclip2:_*lv;
// clip = _*(1/lv):aa.cubic1:_*lv;

// post_gain = it.interpolate_linear(aa.cubic1(resonance) * 1.5, 1, 2/3);
post_gain = 1;

korg_lpf = korg35LPF(normFreq,Q_korg) : _ : _*post_gain;
korg_hpf = korg35HPF(normFreq,Q_korg) : _ : _*post_gain;
// lpf1 = ve.moog_vcf_2bn(resonance*0.99, freq(f2_1));
// lpf2 = ve.moog_vcf_2bn(resonance*0.99, freq(f2_2));
lpf1 = korg35LPF(f2_1,Q_korg-0.2) : _ : _*post_gain;
lpf2 = korg35LPF(f2_2,Q_korg-0.2) : _ : _*post_gain;
// bpf = korg_hpf:korg_lpf; // too much distortion
formant1 = korg_hpf : lpf1;
formant2 = korg_hpf : lpf2;
filter = _<:_,_,_,_ : korg_lpf, korg_hpf, formant1, formant2: ba.selectn(4, mode);

// decimation_filter = fi.lowpass(6, 22000);
decimation_filter = _;

process = _,_ :> _*0.5 : filter : decimation_filter <: _,_;
// osc_freq = hslider("[3]osc freq", 100, 50, 1000, 0.1);
// inputSignal = os.sawtooth(osc_freq);
// process = inputSignal : filter <: _,_;