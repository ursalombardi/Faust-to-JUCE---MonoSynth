import("stdfaust.lib");

// Basic
freq = hslider("h: every/v: Basic/[1]freq", 200, 20, 2000, 0.01) : si.smoo;
gain = hslider("h: every/v: Basic/[2]gain", 1, 0.0, 1.0, 0.01);
gate = checkbox("h: every/v: Basic/[4]gate");

// Waves
sawt = os.sawtooth(freq/1.0125);
sawt2 = os.sawtooth(freq/1.005);
sawt3 = os.sawtooth(freq/0.995);
index = hslider("h: every/v: Basic/[3]index", 0.65, 0.0, 1.0, 0.01) : si.smoo;
index2 = hslider("h: every/v: Basic/[3]index2", 0.95, 0.0, 1.0, 0.01) : si.smoo; 
index3 = hslider("h: every/v: Basic/[3]index3", 0.2, 0.0, 1.0, 0.01) : si.smoo; 
sine = os.oscsin(freq);
czSquare = os.CZsquare(sawt, index) ;
czSaw = os.CZsaw(sawt2, index2);
czPulse = os.CZpulse(sawt3, index3);

nov = 4;
CZ = sine+czSquare/nov+czSaw/nov+czPulse/nov : ve.moog_vcf(res,fr);
CZ2 = czSquare/nov : ve.moog_vcf(res2, fr2);
CZ3 = czSaw/nov : ve.moog_vcf(res3, fr3);
CZ4 = czPulse/4 : ve.moog_vcf(res4, fr4);

// Moog Filters
res = vslider("h: every/h: moog/res", 0.70, 0, 1.00, 0.001) : si.smoo;
fr = vslider("h: every/h: moog/fr", 200, 200, 4000, 0.001) : si.smoo;
res2 = vslider("h: every/h: moog/res2", 0.5, 0, 1, 0.001) : si.smoo;
fr2 = vslider("h: every/h: moog/fr2", 2000, 200, 4000, 0.001) : si.smoo;
res3 = vslider("h: every/h: moog/res3", 0.5, 0, 1, 0.001) : si.smoo;
fr3 = vslider("h: every/h: moog/fr3", 2000, 200, 4000, 0.001) : si.smoo;
res4 = vslider("h: every/h: moog/res4", 0.5, 0, 1, 0.001) : si.smoo;
fr4 = vslider("h: every/h: moog/fr4", 2000, 200, 4000, 0.001) : si.smoo;

// Verb
dt = hslider("dt", 0.1, 0.1, 60, 0.01) : si.smoo;
damp = hslider("damp", 0, 0, 1, 0.01) : si.smoo;
size = hslider("size", 1, 0.5, 3, 0.01) : si.smoo;
early_diff = hslider("earlydiff", 0.5, 0, 1, 0.01) : si.smoo;
feedback = hslider("feedback", 0.5, 0, 1, 0.01) : si.smoo;
mod_depth = hslider("moddepth", 0, 0, 1, 0.01) : si.smoo;
mod_freq = hslider("modfreq", 1, 0, 10, 0.01) : si.smoo;
verbmix = hslider("wetdrymix", 0.5, 0, 1, 0.01)  : si.smoo;
greyHole = re.greyhole(dt, damp, size, early_diff, feedback, mod_depth, mod_freq);
verbdrywetmix = si.bus(inputs(greyHole)) : ef.dryWetMixer(verbmix, greyHole) : si.bus(inputs(greyHole));

// ADR Envelope 
a = hslider("h: adsr/attack", 0.1, 0.01, 2.0, 0.001);
d = hslider("h: adsr/decay", 1, 1,7.0, 0.001);
r = hslider("h: adsr/release", 0.5, 0.0, 5.0, 0.01);
envelope(a,d,s,r,gate) = en.adsre(a,d,0.9,r, gate);

// Tremelo
tremslide = hslider("trem", 1, 0, 6, 0.1);
trem = os.oscsin(tremslide);

brocess = (((CZ + CZ2 + CZ3 + CZ4) * envelope(a,d,1,r,gate))/2) * gain;
brocess2 = (((CZ + CZ2 + CZ3 + CZ4) * trem * envelope(a,d,1,r,gate))/2) * gain;

process = (brocess, brocess2 : select2(checkbox("select"))) <: verbdrywetmix;