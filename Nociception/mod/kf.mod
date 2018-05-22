: kf.mod is the fast K+ current from
: Baker 2005, parameter assignments and formula's from page 854

NEURON {
	SUFFIX kf
	NONSPECIFIC_CURRENT i
	RANGE gbar, ek
	RANGE tau_n, ninf
}

UNITS {
	(S) = (siemens)
	(mV) = (millivolts)
	(mA) = (milliamp)
}

PARAMETER {
	gbar = 3e-5 : =30e-9/(100e-12*1e8) (S/cm2) : 30(nS)/100(um)^2
	ek=-85 (mV)

: Baker 2005 values
	A_anF = 0.00798 (/ms) : A for alpha n
	B_anF = 52.2 (mV)
	C_anF = 1.1 (mV)

	A_bnF = 0.0142 (/ms) : A for beta n
	B_bnF = 55 (mV)
	C_bnF = 10.5 (mV)

: Bostok et al. 1991 values
:	A_anF = 0.129 (/ms) : A for alpha n
:	B_anF = -53 (mV)
:	C_anF = 10 (mV)

:	A_bnF = 0.324 (/ms) : A for beta n
:	B_bnF = -78 (mV)
:	C_bnF = 10 (mV)
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
	g = gbar * n^4
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
	if (-Vm-B_anF != 0) {
		alphan=A_anF*(Vm+B_anF)/(1-exp((-Vm-B_anF)/C_anF))
	} else {
		alphan=A_anF*C_anF
	}
}

FUNCTION betan(Vm (mV)) (/ms) {
	if (Vm+B_bnF != 0) {
		betan=A_bnF*(-B_bnF-Vm)/(1-exp((Vm+B_bnF)/C_bnF))
	} else {
		betan=A_bnF*C_bnF
	}
}

FUNCTION rates(Vm (mV)) (/ms) {
	tau_n = 1.0 / (alphan(Vm) + betan(Vm))
	ninf = alphan(Vm) * tau_n
}
