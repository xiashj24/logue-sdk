import("stdfaust.lib");
mode = hslider("[0]mode", 0, 0, 2, 1);
normFreq = hslider("[1]freq",1,0,1,0.001) : si.smoo;
Q = hslider("[2]resonance", 0, 0, 1, 0.001), 0.5, 9.7 : it.interpolate_linear : si.smoo;

bandwidth = normFreq, 0.10, 0.05: it.interpolate_linear;
bpf = _ : ve.korg35HPF(max(normFreq - bandwidth/2, 0),Q) : ve.korg35LPF(min(normFreq+bandwidth/2, 1),Q);
lpf = ve.korg35LPF(normFreq,Q);
hpf = ve.korg35HPF(normFreq,Q);
filter = _<:_,_,_ : lpf, bpf, hpf: ba.selectn(3, mode);

process = _,_ :> filter*0.5 <: _,_;
// inputSignal = os.sawtooth(100); 
// process = inputSignal : filter <: _,_;