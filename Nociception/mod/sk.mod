TITLE sk
: Calcium activated K channel.

UNITS {
	(molar) = (1/liter)
}

UNITS {
	(mV) =	(millivolt)
	(mA) =	(milliamp)
	(mM) =	(millimolar)
	PI		= (pi) (1)
}


NEURON {
	SUFFIX sk
	USEION ca READ cai
	USEION k READ ek WRITE ik
	RANGE gkca, gkbar, ik, qk
	GLOBAL hill, kd
}

UNITS {
	FARADAY		= 96485.309 (coul)
	R = 8.313424 (joule/degC)
}

PARAMETER {
	celsius		(degC)
	gkbar=.01	(mho/cm2)
	hill = 4.7
	kd = 3e-4
}

ASSIGNED {
	gkca		(mho/cm2)
	v		(mV)
	ik		(mA/cm2)
	ek		(mV)
	cai		(mM)
	diam		(um)
}
STATE { qk }

INITIAL {
	VERBATIM
	cai = _ion_cai;
	ENDVERBATIM
	gkca = hillfunction(cai)
	ik = gkca*(v - ek)
	qk=0
}


BREAKPOINT {
	SOLVE kstate METHOD sparse
	gkca = hillfunction(cai)
	ik = gkca*(v - ek)
}

KINETIC kstate {
	COMPARTMENT diam*diam*PI/4 { qk }
	~ qk << (-ik*diam *PI*(1e4)/FARADAY )
}

FUNCTION hillfunction(ci) {
	hillfunction = gkbar/(1+(kd/ci)^hill)
}
