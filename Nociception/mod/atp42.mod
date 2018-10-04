TITLE 3D diffusion
NEURON{
	POINT_PROCESS AtP_42
	RANGE    atp,rPSD,h,nu,dir,spill,c0cleft
	RANGE Deff,meandist,rabs,alpha,h,Rmf  
	RANGE includir,incluspill, Popeak,alpha,Podir,Pospill 
	RANGE ts1,td1,tm1,k, tx1}

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
	alpha=5 
	Deff=0.2 (um2/ms):effective diffusion coefficient
	c0cleft = 1 (mM):initial quantity atp
	rPSD=0.28 (um) :  radius 
	meandist=0.29 (um) : lowest limit
	a=0.02 (um)
	Popeak=0.6
	includir=1 : inclusion of direct component
	incluspill=1 : inclusion of spillover component
	h(um2)
	k
	atp2

 }
ASSIGNED{
   tx1(ms)
   dir (mM)
   spill(mM)
   atp (mM)
   Podir
   Pospill 
}
INITIAL {
	tx1=30
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
	dir= (2*c0cleft*alpha/(sqrt(4*PI*Deff*(t-tx1))*sqrt(4*PI*Deff*(t-tx1))*sqrt(4*PI*Deff*(t-tx1))))*(1-exp(h/(4*Deff*(tx1-t))))
	if(dir>c0cleft){dir=c0cleft}
	spill = 2*nu*c0cleft*rPSD*rPSD*PI*alpha*(1/sqrt(4*PI*Deff*(t-tx1)))*(exp(meandist*meandist/(4*Deff*(tx1-t)))-exp(rPSD*rPSD/(4*Deff*(tx1-t))))
	:atp= (2*c0cleft*PI*a*alpha*rPSD*rPSD*exp(h/(4*Deff*(tx1-t))+k*(tx1-t)))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-tx1)*(t-tx1)*(t-tx1))
   	:atp2= (2*c0cleft*PI*a*alpha*rPSD*rPSD*exp(-h/(4*Deff*(tx1-t))-k))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-tx1)*(t-tx1)*(t-tx1))
    atp= (2*c0cleft*PI*a*alpha*rPSD*rPSD*exp(k*(tx1-t)+h/(4*Deff*(tx1-t))))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-tx1)*(t-tx1)*(t-tx1))
    if(atp>c0cleft){atp=c0cleft}

    :atp= ((2*c0cleft)*exp(h/(4*Deff*(tx1-t))))/(sqrt(4*PI*Deff*(t-tx1))*sqrt(4*PI*Deff*(t-tx1))*sqrt(4*PI*Deff*(t-tx1)))
   
: Experimental waveforms
Podir=(0.94*exp((tx1-t)/0.37(ms))+0.06*exp((tx1-t)/2.2(ms))
  -exp((tx1-t)/0.199(ms)))/0.249*(0.43/0.484)*Popeak
Pospill=(0.39*exp((tx1-t)/2.0(ms))+0.61*exp((tx1-t)/9.1(ms))-
 exp((tx1-t)/0.44(ms)))/0.682*(0.125/0.484)*Popeak
}
}
NET_RECEIVE (weight)
{
tx1=t 
}




