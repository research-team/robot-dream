NEURON {
	POINT_PROCESS p2x2
		POINTER patp
	RANGE C1, C2, C3, C4, F5, O6, O7, F8
	RANGE g, gmax, Ev
	NONSPECIFIC_CURRENT i}

UNITS{
	(nA) = (nanoamp)
	(molar) = (1/liter)
	(uM) = (micromolar)
	(mV) = (millivolt)
	(pS) = (picosiemens)
}

PARAMETER {

	kon1 = 15.98 (/uM /s) 
	kon2 = 16.3 (/uM /s) 
	kon3 = 11.6 (/uM /s) 
	koff1 = 0.019 (/s) 
	koff2 = 380 (/s) 
	koff3 =	6822 (/s) 
	delta = 3718 (/s) 
	gamma = 43.54 (/s) 
	alfa1 = 1088 (/s) 
	beta1 = 540 (/s) 
	alfa2 = 0.246 (/s) 
	beta2 = 0.033 (/s) 
	sigma1 = 31.16 (/s) 
	eps1 = 79 (/s) 
	sigma2 = 4.53 (/s) 
	eps2 = 3.20 (/s) 	
	gmax = 32.4 (pS)	: conductance     
	Ev = -40 (mV) 
	
}

ASSIGNED {
	v (mV)	: voltage	
	i (nA)	: current
	g  (pS)	: conductance 	
    patp (uM) : concentration
    k1 (/s)   : binding
    k2 (/s)   : binding
    k3 (/s)   : binding
}

STATE {	
	C1
	C2
	C3
	C4
	F5
	O6
	O7
	F8
}

INITIAL {
	C1=1
}

BREAKPOINT {
	SOLVE kstates METHOD sparse
	g = gmax*(O6 + O7)*(1e+9)	
	i = g * (v - Ev)
}

KINETIC kstates{

	k1 = kon1*patp
    k2 = kon2*patp
    k3 = kon3*patp

	~ C1 <-> C2 (k1, koff1)
	~ C2 <-> C3 (k2, koff2)
	~ C3 <-> C4 (k3, koff3)
	~ C4 <-> F5 (delta, gamma)
	~ F5 <-> O6 (beta1, alfa1)
	~ F5 <-> O7 (beta2, alfa2)
	~ F8 <-> O6 (eps1, sigma1)
	~ F8 <-> O7 (eps2, sigma2)
	

	CONSERVE C1+C2+C3+C4+F5+O6+O7+F8=1
}