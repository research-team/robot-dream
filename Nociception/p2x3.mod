NEURON {
	POINT_PROCESS p2x3
		POINTER patp
	RANGE K1, L1, K2, L2, K3, L3, K4, L4, R4, D4, R3, D3, R2, D2
	RANGE Re, AR, A2R, A3R, Ro, AD, A2D, A3D
	RANGE g, gmax
	NONSPECIFIC_CURRENT i}

UNITS{
	(nA) = (nanoamp)
	(molar) = (1/liter)
	(mM) = (millimolar)
	(mV) = (millivolt)
	(pS) = (picosiemens)
}

PARAMETER {

	K1 = 120000 (/mM /s)  
	L1 = 20 (/s)
	K2 = 80000 (/mM /s)
	L2 = 40 (/s)
	K3 = 40000 (/mM /s)
	L3 = 40 (/s)
	K4 = 70 (/s)
	L4 = 1 (/s)
	R4 = 0.00001 (/s)
	D4 = 0.00001 (/s)
	R3 = 0.00001 (/s)
	D3 = 0.00001 (/s) 
	R2 = 0.00001 (/s) 
	D2 = 0.00001 (/s)

	gmax = 32.4 (pS)	: conductance     
	Ev = -80 (mV) 
	
}

ASSIGNED {
	v (mV)	: voltage	
	i (nA)	: current
	g  (pS)	: conductance 	
    patp (mM) : concentration
    k1 (/s)   : binding
    k2 (/s)   : binding
    k3 (/s)   : binding

}

STATE {	
	Re
	AR
	A2R
	A3R
	Ro
	AD
	A2D
	A3D
}

INITIAL {
	Re=1
}

BREAKPOINT {
	SOLVE kstates METHOD sparse
	g = gmax * Ro
	i = (1e-3) * g * (v - Ev)
}

KINETIC kstates{

	k1 = K1*patp
    k2 = K2*patp
    k3 = K3*patp

	~ Re <-> AR (k1, L1)
	~ AR <-> A2R (k2, L2)
	~ A2R <-> A3R (k3, L3)
	~ A3R <-> Ro (K4, L4)
	~ A3R <-> A3D (D4, R4)
	~ A2R <-> A2D (D3, R3)
	~ AR <-> AD (D2, R2)

	CONSERVE Re+AR+A2R+A3R+Ro+AD+A2D+A3D=1
}
