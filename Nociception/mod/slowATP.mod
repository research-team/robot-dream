TITLE slow ATP diffusion
NEURON{
	POINT_PROCESS AtP_slow
	RANGE atp,h,c0cleft
	RANGE tx1, k, hydrolysis}

UNITS{
		(molar)=(1/liter)
		(uM)=(micromolar)
		(um)=(micron)
		(nA)=(nanoamp)
}
CONSTANT {
	PI=3.1415927
}
PARAMETER { 
	c0cleft = 1 (uM):initial quantity atp
	h(um)
	tx1(ms)
	k = 10

 }
ASSIGNED{
   atp (uM)
   hydrolysis (uM)
}
INITIAL {
	:tx1=10
	atp=0
}
BREAKPOINT
{
	at_time(tx1)
	if (t<=tx1){
		atp=0
}
if(t>tx1) {
UNITSOFF
	hydrolysis  = 0.1*c0cleft*(1-exp(k*(tx1-t)))
	atp = c0cleft*(1-exp(0.00025*(tx1-t))) - hydrolysis
    if(atp>c0cleft){atp=c0cleft}
    if(atp<0){atp=0}
}
}
NET_RECEIVE (weight)
{
tx1=t 
}




