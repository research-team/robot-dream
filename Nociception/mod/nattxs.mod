: nattxs.mod is a transient ttx-sensitive Na+ current from
: Baker 2005, parameter assignments and formula's from page 854

NEURON {
	SUFFIX nattxs
	NONSPECIFIC_CURRENT i
	RANGE gbar, ena
}

UNITS {
	(S) = (siemens)
	(mV) = (millivolts)
	(mA) = (milliamp)
}

PARAMETER {
	gbar = 1.8e-6 : =18e-9/(100e-12*1e8) (S/cm2) : 18(nS)/100(um)^2
	ena=50.6 (mV)

	A_am = 17.235 (/ms) : A for alpha m
	B_am = 7.58 (mV)
	C_am = -11.47 (mV)

	A_ah = 0.23688 (/ms) : A for alpha h
	B_ah = 115 (mV)
	C_ah = 46.33 (mV)

	A_bm = 17.235 (/ms) : A for beta m
	B_bm = 66.2 (mV)
	C_bm = 19.8 (mV)

	A_bh = 10.8 (/ms)   : A for beta h
	B_bh = -11.8 (mV)
	C_bh = -11.998 (mV)
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
	g = gbar * m^3 * h
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

FUNCTION alpham(Vm (mV)) (/ms) {
	alpham=A_am/(1+exp((Vm+B_am)/C_am))
}

FUNCTION alphah(Vm (mV)) (/ms) {
	alphah=A_ah*exp(-(Vm+B_ah)/C_ah)
}

FUNCTION betam(Vm (mV)) (/ms) {
	betam=A_bm/(1+exp((Vm+B_bm)/C_bm))
}

FUNCTION betah(Vm (mV)) (/ms) {
	betah=A_bh/(1+exp((Vm+B_bh)/C_bh))
}

FUNCTION rates(Vm (mV)) (/ms) {
	tau_m = 1.0 / (alpham(Vm) + betam(Vm))
	minf = alpham(Vm) * tau_m

	tau_h = 1.0 / (alphah(Vm) + betah(Vm))
	hinf = alphah(Vm) * tau_h
}
