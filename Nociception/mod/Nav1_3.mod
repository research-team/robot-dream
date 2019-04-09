NEURON	{
	SUFFIX Nav1_3
	USEION na READ ena WRITE ina
	RANGE gNav1_3bar, gNav1_3, ina, BBiD, hTau, gbar 
}

UNITS	{
	(S) = (siemens)
	(mV) = (millivolt)
	(mA) = (milliamp)
}

PARAMETER	{
	gbar = 0.00001 (S/cm2) 
	BBiD = 122 
}

ASSIGNED	{
	v	(mV)
	ena	(mV)
	ina	(mA/cm2)
	gNav1_3	(S/cm2)
	mInf
	mTau
	mAlpha
	mBeta
	hInf
	hTau
}

STATE	{ 
	m
	h
}

BREAKPOINT	{
	SOLVE states METHOD cnexp
	gNav1_3 = gbar*m*m*m*h
	ina = gNav1_3*(v-ena)
}

DERIVATIVE states	{
	rates()
	m' = (mInf-m)/mTau
	h' = (hInf-h)/hTau
}

INITIAL{
	rates()
	m = mInf
	h = hInf
}

PROCEDURE rates(){
	UNITSOFF
		if(v == -26){
			v = v + 0.000001
		}
		mAlpha = (0.182 * ((v)- -26))/(1-(exp(-((v)- -26)/9)))
		if(v == -26){
			v = v + 0.000001
		}
		mBeta = (0.124 * (-(v) -26))/(1-(exp(-(-(v) -26)/9)))
		mInf = mAlpha/(mAlpha + mBeta)
		mTau = 1/(mAlpha + mBeta) 
		hInf = 1 /(1+exp((v-(-65.0))/8.1)) 
		hTau = 0.40 + (0.265 * exp(-v/9.47))
	UNITSON
}