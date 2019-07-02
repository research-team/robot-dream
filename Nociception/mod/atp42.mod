TITLE 3D diffusion
NEURON{
	POINT_PROCESS AtP_42
	RANGE atp,h,c0cleft,initial
	RANGE Deff,tx1,k}

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
	nu=1(/um2)
	Deff=0.2 (um2/ms):effective diffusion coefficient
	c0cleft = 1 (uM):initial quantity atp
	h(um) : distance from point of application
	tx1(ms) : time of application 
	k=1 :degradation coefficient 
	initial = 0 : quantity atp from previous point
	txlast : time of application from previous point

 }
ASSIGNED{
   atp (uM)
   initialdiff (uM)
}
INITIAL {
	:tx1=10
	atp=0 
	txlast=tx1
	initialdiff=0
}
BREAKPOINT
{
	at_time(tx1)
	if (t<=tx1){
		atp=initial
	}
	if(t>tx1){
	UNITSOFF
		if (initial>0){initialdiff = (2*c0cleft*exp(k*(txlast-t)+h/(4*Deff*(txlast-t))))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-txlast)*(t-txlast)*(t-txlast))}
		atp = initialdiff + (2*c0cleft*exp(k*(tx1-t)+h/(4*Deff*(tx1-t))))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-tx1)*(t-tx1)*(t-tx1))
	    if(atp>c0cleft){atp=c0cleft}
	}
}
NET_RECEIVE (weight)
{
tx1=t 
}
