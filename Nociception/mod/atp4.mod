TITLE 3D diffusion
NEURON{
	POINT_PROCESS AtP_4
	RANGE atp,initial,c0cleft
	RANGE Deff,h,tx1}

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
	Deff=0.2 (um2/ms):effective diffusion coefficient
	c0cleft = 1 (uM):initial quantity atp
	h(um) : distance from point of application
	tx1(ms) : time of application 
	initial = 0 : quantity atp from previous point

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
		atp=initial
}
if(t>tx1) {
UNITSOFF
	atp= (2*c0cleft*exp(h/(4*Deff*(tx1-t))))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-tx1)*(t-tx1)*(t-tx1))
    if(atp>c0cleft){atp=c0cleft}
}
}
NET_RECEIVE (weight)
{
tx1=t 
}




