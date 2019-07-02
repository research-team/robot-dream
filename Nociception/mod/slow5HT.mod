TITLE slow 5HT diffusion
NEURON{
	POINT_PROCESS slow_5HT
	RANGE serotonin,h,c0cleft, diff
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
	c0cleft = 20 (uM):initial quantity atp
	h(um)
	tx1(ms)
	k = 0.00055
	vmax = 0.0175 
	km = 0.005
	a = 30 :coefficient of reuptake
 }
ASSIGNED{
   serotonin (uM)
   diff (uM)
}
INITIAL {
	:tx1=10
	serotonin=0
	diff = 0
}
BREAKPOINT
{
	at_time(tx1)
	if (t<=tx1){
		serotonin=0
		diff = 0
	}
if(t>tx1) {
UNITSOFF
	diff = (t-tx1)*0.00005
    if(diff>c0cleft){diff=c0cleft}
    serotonin = diff - a*((vmax*diff)/(km + diff))
    if(serotonin > c0cleft){serotonin=c0cleft}
    if(serotonin < 0){serotonin=0}
}
}
NET_RECEIVE (weight)
{
tx1=t 
}




