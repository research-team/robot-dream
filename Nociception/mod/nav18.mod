
NEURON {
	SUFFIX nav18
	NONSPECIFIC_CURRENT i
	RANGE gbar, ena, slow_inact, m, h, s, gate
	RANGE tau_m, tau_h, tau_s
	: if slow_inact=1 then ultra-slow inactivation is included
}

UNITS {
	(S) = (siemens)
	(mV) = (millivolts)
	(mA) = (milliamp)
}

PARAMETER {
	gbar = 0.005 (S/cm2)
	ena=55 (mV)

	slow_inact = 1 (1) : to turn on ultra slow inactivation
}

ASSIGNED {
	v	(mV) : NEURON provides this
	i	(mA/cm2)
	g	(S/cm2)
	tau_h	(ms)
	tau_m	(ms)
	tau_s	(ms)
	minf
	hinf
	sinf
}

STATE { m h s}

BREAKPOINT {
	SOLVE states METHOD cnexp
	g = gbar * m*m*m * h * s
	i = g * (v-ena)
}

INITIAL {
	rates(v) : set time constants and infinity values
	: assume that equilibrium has been reached
	m = minf
	h = hinf
	s = sinf
}

DERIVATIVE states {
	rates(v)
	m' = (minf - m)/tau_m
	h' = (hinf - h)/tau_h
	s' = (sinf - s)/tau_s
}

FUNCTION alpham(Vm (mV)) (/ms) {
	alpham = (0.05*(1+exp(Vm+44)/8))/(1+exp((Vm-7)/10))
}

FUNCTION alphah(Vm (mV)) (/ms) {
	alphah = 0.0008*(exp(-Vm/30))
}

FUNCTION betam(Vm (mV)) (/ms) {
	betam = 0.05*(1+exp(-(Vm+6)/16))
}

FUNCTION betah(Vm (mV)) (/ms) {
	betah = 0.22/(1+0.24*exp(-Vm/7))
}

FUNCTION alphas(Vm (mV)) (/ms) {
	alphas=0.0001*(exp(-(Vm+8)/29))+0.0008
}

FUNCTION betas(Vm (mV)) (/ms) {
	betas=0.003/(1+0.24*exp(-(Vm+23)/10))
}

FUNCTION rates(Vm (mV)) (/ms) {
	tau_m = 1.0 / (alpham(Vm) + betam(Vm))
	minf = alpham(Vm) * tau_m

	tau_h = 1.0 / (alphah(Vm) + betah(Vm))
	hinf = alphah(Vm) * tau_h

	if (slow_inact) {
		tau_s = 1.0 / (alphas(Vm) + betas(Vm))
		sinf = alphas(Vm) * tau_s
	} else {
		tau_s = 0.1	: in a tenth of a millisecond we move to within
		sinf = 1.0	: 1/e factor towards s = 1
	}
}
