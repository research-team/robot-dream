NEURON {
	SUFFIX na
	USEION na READ ena WRITE ina
	RANGE gna, gmax
	RANGE I1, I2, I3, I4, I5, C1, C2, C3, C4, Go
	GLOBAL A1, B1, C, D1, E1, F1, G1, H1, J1, G2, H2, J2
}


UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
	(pS) = (picosiemens)
	(um) = (micron)

} 

PARAMETER {

	A1 = 44.178
	B1 = 0.2
	C = 51.5
	D1 = 0.88357
	E1 = 14.07
	F1 = 0.5
	G1 = 1.3254
	H1 = 40.0
	J1 = 0.09
	G2 = 0.27878
	H2 = 20.0
	J2 = 1.0

	gmax = 58.2 (pS/um2)	: conductance     

}


ASSIGNED {
	ina 	(mA/cm2)
	gna		(pS/um2)
	ena		(mV)
	am		(mV)
	a1 		(ms)
	bm		(mV)
	b1  	(ms)
	v (mV)	: voltage	
}

STATE {	
	I1
	I2
	I3
	I4
	I5
	C1
	C2
	C3
	C4
	Go
}

INITIAL {
	C1=1
}

BREAKPOINT {
    SOLVE kstates METHOD sparse
    gna = gmax*Go*Go*Go*C1
    ina = (1e-4) * gna * (v - ena)
} 

KINETIC kstates{

	am = A1/(1+exp(-B1 * (v + C))) + D1 * (v + E1)/(1 - exp(-F1 * (v + E1)))
    a1 = D1 * (v + E1)/(1 - exp(-F1 * (v + E1)))
    bm = -G1 * (v + H1)/(1 - exp(J1 * (v + H1)))
    b1 = -G2 * (v + H2)/(1 - exp(J2 * (v + H2)))

	~ I1 <-> I2 (4*am, bm)
	~ I2 <-> I3 (3*am, 2*bm)
	~ I3 <-> I4 (2*am, 3*bm)
	~ I4 <-> I5 (am, 4*bm)
	~ C1 <-> I1 (0, b1)
	~ C2 <-> I2 (0, b1)
	~ C3 <-> I3 (0, b1)
	~ C4 <-> I4 (0, b1)
	~ C1 <-> C2 (4*am, bm)
	~ C2 <-> C3 (3*am, 2*bm)
	~ C3 <-> C4 (2*am, 3*bm)
	~ C4 <-> Go (am, 4*bm)
	~ Go <-> I5 (a1, 0)


	CONSERVE I1+I2+I3+I4+I5+C1+C2+C3+C4+Go=1
}





