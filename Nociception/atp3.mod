TITLE 3D diffusion
NEURON{
	POINT_PROCESS AtP_3
	RANGE    atp,rPSD,h,nu,dir,spill
	RANGE Deff,meandist,rabs,alpha,h,Rmf  
	RANGE includir,incluspill, Popeak,alpha,Podir,Pospill 
	RANGE ts1,td1,tm1}

UNITS{
		(molar)=(1/liter)
		(mM)=(millimolar)
		(um)=(micron)
		(nA)=(nanoamp)
}
CONSTANT {
	PI=3.1415927
}
PARAMETER { 
	nu=1(/um2)
	alpha=0.5 
	Deff=0.8 (um2/ms):effective diffusion coefficient
	c0cleft = 1 (mM):initial quantity atp
	rPSD=0.11 (um) :  radius 
	meandist=0.29 (um) : lowest limit
	Rmf=2.9(um) :radius 
	:h = 0.02(um)
	Popeak=0.6
	includir=1 : inclusion of direct component
	incluspill=1 : inclusion of spillover component
 }
ASSIGNED{
   tx1(ms)
   dir (mM)
   spill(mM)
   atp (mM)
   h(um)
   Podir
   Pospill 
}
INITIAL {
	tx1=10
	atp=0
	dir=0
	spill=0
}
BREAKPOINT
{
	at_time(tx1)
	if (t<=tx1){
		atp=0
		dir=0
		spill=0
		Podir=0
		Pospill=0
}
if(t>tx1) {
UNITSOFF
	c0cleft=c0cleft+0.00005
	atp= (2*c0cleft*PI*alpha*rPSD*rPSD*exp(h/(4*Deff*(tx1-t))))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-tx1)*(t-tx1)*(t-tx1))

}
}
NET_RECEIVE (weight)
{
tx1=t 
}




