NEURON {
	POINT_PROCESS p2x3
		POINTER patp
	RANGE ko, kd, kr, kb, kc, g, gmax, Ev
}

UNITS{
	(nA) = (nanoamp)
	(molar) = (1/liter)
	(mM) = (millimolar)
	(mV) = (millivolt)
	(pS) = (picosiemens)
}

PARAMETER {

	ko	= 70 (/s) 				
	kc	= 1	(/s)				
	kd	= 23 (/s)					
	kr	= 0.1 (/s)			
    kb  = 0.5 (mM)    

	gmax = 300 (pS)	: conductance     
	Ev = 0 (mV) 
	
}

ASSIGNED {
	v (mV)		
	i (nA)	:current
	g  (pS)	: conductance 	
    patp (mM): concentration
    celsius  (degC)

}

STATE {	
	C
	O
	D
}

INITIAL {
	C=1
	O=0
	D=0	
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	g = gmax * O
	i = (1e-6) * g * (v - Ev)
}

DERIVATIVE states {
	LOCAL kon, Q10
	Q10 = 2^((celsius-37(degC))/10(degC)) 
	kon = ko*patp^2/(patp+kb)^2	
	C'=(0.001)*Q10*(-kon*C+kc*O)
	D'=(0.001)*Q10*(-kr*D+kd*O)
	O'=(0.001)*Q10*(-(kc+kd)*O+kon*C+kr*D)		
}