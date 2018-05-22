: nav1p8.mod is the NaV1.8 Na+ current from
: Baker 2005, parameter assignments and formula's from page 854

NEURON {
	SUFFIX nav1p8
	NONSPECIFIC_CURRENT i
	RANGE gbar, ena
}

UNITS {
	(S) = (siemens)
	(mV) = (millivolts)
	(mA) = (milliamp)
}

PARAMETER {
	gbar = 0.5 : =220e-9/(100e-12*1e8) (S/cm2) : 220(nS)/100(um)^2
	ena=55 (mV)

	A_am8 = 3.83 (/ms) : A for alpha m(8 etc ...)
	B_am8 = 25.58 (mV)
	C_am8 = -11.47 (mV)

	A_ah8 = 0.013536 (/ms) : A for alpha h
	B_ah8 = 105 (mV)
	C_ah8 = 46.33 (mV)

	A_bm8 = 6.894 (/ms) : A for beta m
	B_bm8 = 41.2 (mV)
	C_bm8 = 29.8 (mV)

	A_bh8 = 0.61714 (/ms)   : A for beta h
	B_bh8 = -21.8 (mV)
	C_bh8 = -11.998 (mV)
}

ASSIGNED {
	v	(mV) : NEURON provides this
	i	(mA/cm2)
	g	(S/cm2)
	tau_h	(ms)
	tau_m	(ms)
	minf
	hinf
}

STATE { m h }

BREAKPOINT {
	SOLVE states METHOD cnexp
	g = gbar * m*m*m * h
	i = g * (v-ena)
}

INITIAL {
	: assume that equilibrium has been reached
	m = alpham(v)/(alpham(v)+betam(v))
	h = alphah(v)/(alphah(v)+betah(v))
}

DERIVATIVE states {
	rates(v)
	m' = (minf - m)/tau_m
	h' = (hinf - h)/tau_h
}


UNITSOFF
FUNCTION alpham(Vm (mV)) (/ms) {
	: alpham=A_am8/(1+exp((Vm+B_am8)/C_am8))
	alpham = (0.05*(1+(exp(Vm+44))/8))/(1+exp((Vm-7)/10))
}

FUNCTION alphah(Vm (mV)) (/ms) {
	:alphah=A_ah8*exp(-(Vm+B_ah8)/C_ah8)
	alphah = 0.0008*(exp(-Vm/30))
}

FUNCTION betam(Vm (mV)) (/ms) {
	: betam=A_bm8/(1+exp((Vm+B_bm8)/C_bm8))
	betam = 0.05*(1+exp(-(Vm+6)/16))
}

FUNCTION betah(Vm (mV)) (/ms) {
	: betah=A_bh8/(1+exp((Vm+B_bh8)/C_bh8))
	betah = 0.22/(1+0.24*exp(-Vm/7))
}

FUNCTION rates(Vm (mV)) (/ms) {
	tau_m = 1.0 / (alpham(Vm) + betam(Vm))
	minf = alpham(Vm) * tau_m

	tau_h = 1.0 / (alphah(Vm) + betah(Vm))
	hinf = alphah(Vm) * tau_h
}
