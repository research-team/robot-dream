: ks.mod is the slow K+ current from
: Baker 2005, parameter assignments and formula's from page 854
: bug fix by Marcus Petersson 20100215 (see gating variable power)

NEURON {
	SUFFIX ks
	NONSPECIFIC_CURRENT i
	RANGE gbar, ena
}

UNITS {
	(S) = (siemens)
	(mV) = (millivolts)
	(mA) = (milliamp)
}

PARAMETER {
	gbar = 0.2e-5 : =2e-9/(100e-12*1e8) (S/cm2) : 2(nS)/100(um)^2
	ek=-85 (mV)

	A_anS = 0.00122 (/ms) : A for alpha n
	B_anS = -10.5 (mV)
	C_anS = 13.6 (mV)

	A_bnS = 0.000739 (/ms) : A for beta n
	B_bnS = 47.1 (mV)
	C_bnS = 10.8 (mV)
}

ASSIGNED {
	v	(mV) : NEURON provides this
	i	(mA/cm2)
	g	(S/cm2)
	tau_n	(ms)
	ninf
}

STATE { n }

BREAKPOINT {
	SOLVE states METHOD cnexp
	g = gbar * n : not n^4 bug fix by Marcus Petersson 20100215
	i = g * (v-ek)
}

INITIAL {
	: assume that equilibrium has been reached
	n = alphan(v)/(alphan(v)+betan(v))
}

DERIVATIVE states {
	rates(v)
	n' = (ninf - n)/tau_n
}

FUNCTION alphan(Vm (mV)) (/ms) {
	if (-Vm-B_anS != 0) {
		alphan=A_anS*(Vm+B_anS)/(1-exp((-Vm-B_anS)/C_anS))
	} else {
		alphan=A_anS*C_anS
	}
}

FUNCTION betan(Vm (mV)) (/ms) {
	if (Vm+B_bnS != 0) {
		betan=A_bnS*(-B_bnS-Vm)/(1-exp((Vm+B_bnS)/C_bnS))
	} else {
		betan=A_bnS*C_bnS
	}
}

FUNCTION rates(Vm (mV)) (/ms) {
	tau_n = 1.0 / (alphan(Vm) + betan(Vm))
	ninf = alphan(Vm) * tau_n
}
