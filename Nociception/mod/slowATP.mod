TITLE slow ATP diffusion
NEURON{
	POINT_PROCESS AtP_slow
	RANGE atp,h,c0cleft
	RANGE tx1}

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

 }
ASSIGNED{
   atp (uM)
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
	atp = (t-tx1)*0.00025
    if(atp>c0cleft){atp=c0cleft}
}
}
NET_RECEIVE (weight)
{
tx1=t 
}




