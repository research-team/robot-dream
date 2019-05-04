NEURON {
	POINT_PROCESS r5ht3a
		POINTER serotonin
	RANGE Re, AR, A2R, A3R, Ob, Oi, Ol, C1, C2, AD, A2D, A3D, D
	RANGE g, gmax, Ev
	NONSPECIFIC_CURRENT i}

UNITS{
	(pA) = (picoamp)
	(molar) = (1/liter)
	(uM) = (micromolar)
	(mV) = (millivolt)
	(pS) = (picosiemens)
}

PARAMETER {

	k11 = 50000000 (/molar)  
	k12 = 150 
	k21 = 40000000 (/molar)
	k22 = 300
	k31 = 30000000 (/molar)
	k32 = 450 
	k41 = 55
	k42 = 300
	k51 = 165
	k52 = 150 
	o11 = 0.02 
	o12 = 330
	o31 = 18000 
	o32 = 6500
	o41 = 1500 
	o42 = 350
	o51 = 11 
	o52 = 11500
	o61 = 0.01 
	o62 = 1.2
	o71 = 5100 
	o72 = 5400
	d11 = 50000000 (/molar)  
	d12 = 0.27
	d21 = 40000000 (/molar)  
	d22 = 0.54
	d31 = 30000000 (/molar)  
	d32 = 0.81 
	d41 = 0.01
	d42 = 1.5  


	gmax = 0.31 (pS)	: conductivity     
	Ev = 28 (mV) 	
}

ASSIGNED {
	v (mV)	: voltage	
	i (pA)	: current
	g  (pS)	: conductance 	
    serotonin (uM) : concentration
    k1 (/s)   : binding
    k2 (/s)   : binding
    k3 (/s)   : binding
    d1 (/s)   
    d2 (/s)   
    d3 (/s)  
}

STATE {	
	Re 
	AR
	A2R
	A3R
	Ob
	Oi
	Ol
	C1
	C2
	AD
	A2D
	A3D
	D
}

INITIAL {
	Re=1
}

BREAKPOINT {
	SOLVE kstates METHOD sparse
	g = gmax*(Ol+Oi+Ob)
	i = (1e-3) * g * (v - Ev)
}

KINETIC kstates{

	k1 = k11*serotonin
    k2 = k21*serotonin
    k3 = k31*serotonin

    d1 = d11*serotonin
    d2 = d21*serotonin
    d3 = d31*serotonin


	~ Re <-> AR (k1, k12)
	~ Re <-> D (d41, d42)
	~ AR <-> A2R (k2, k22)
	~ A2R <-> A3R (k3, k32)
	~ A3R <-> Ob (k41, k42)
	~ A3R <-> Oi (k51, k52)
	~ Ol <-> A3R (o11, o12)
	~ Ol <-> C1 (o51, o52)
	~ C1 <-> Oi (o41, o42)
	~ C1 <-> Ob (o31, o32)
	~ A3D <-> Ol (o61, o62)
	~ C2 <-> C1 (o71, o72)
	~ D <-> AD (d11, d12)
	~ AD <-> A2D (d21, d22)
	~ A2D <-> A3D (d31, d32)

	CONSERVE Re+AR+A2R+A3R+Ob+Oi+Ol+C1+C2+AD+A2D+A3D+D=1
}