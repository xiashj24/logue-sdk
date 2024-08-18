import("stdfaust.lib");
mode = hslider("[0]mode", 0, 0, 4, 1);
normFreq = hslider("[1]freq",1,0,1,0.001) : si.smoo;
Q = hslider("[2]resonance", 0, 0, 1, 0.001), 0.5, 9.8 : it.interpolate_linear : si.smoo;


f2_1 = normFreq, 0.7869762832625042, 0.507155667499064: it.interpolate_linear;
f2_2 = normFreq, 0.48899786615997504, 0.6235193962753848: it.interpolate_linear;

lpf = ve.korg35LPF(normFreq,Q);
hpf = ve.korg35HPF(normFreq,Q);
bpf = hpf : lpf;
formant1 = hpf : ve.korg35LPF(f2_1,Q);
formant2 = hpf : ve.korg35LPF(f2_2,Q);
filter = _<:_,_,_,_,_ : lpf, bpf, hpf, formant1, formant2: ba.selectn(5, mode);

process = _,_ :> filter*0.5 <: _,_;
// osc_freq = hslider("[3]osc freq", 100, 50, 1000, 0.1);
// inputSignal = os.sawtooth(osc_freq); 
// process = inputSignal : filter <: _,_;