TITLE 3D diffusion
NEURON{
	POINT_PROCESS diff_5HT
	RANGE   serotonin,h,c0cleft
	RANGE 	Deff,tx1, diff, a}

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
	Deff= 0.000465 (um2/ms):effective diffusion coefficient
	c0cleft = 2 (uM):initial quantity atp
	h(um)
	tx1(ms)
	k = 0.00055
	vmax = 0.0175 
	km = 0.005
	a = 20 :coefficient of reuptake

 }
ASSIGNED{
   serotonin (uM)
   diff (uM)
}
INITIAL {
	:tx1=10
	serotonin = 0
	diff = 0
}

BREAKPOINT
{
	at_time(tx1)
	if (t<=tx1){
		serotonin = 0
		diff = 0 
}
if(t>tx1) {
UNITSOFF
	diff = (2*c0cleft*exp(h/(4*Deff*(tx1-t))))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-tx1)*(t-tx1)*(t-tx1))
	serotonin = diff - a*((vmax*diff)/(km + diff))
    if(serotonin > c0cleft){serotonin=c0cleft}
    if(serotonin < 0){serotonin=0}
}
}
NET_RECEIVE (weight)
{
tx1=t 
}




