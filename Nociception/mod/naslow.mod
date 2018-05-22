COMMENT
State-dependent Na channel model exhibiting only fast slow inactivation
Menon V, Spruston N, Kath WL, 2009
ENDCOMMENT

NEURON{
SUFFIX naslow
USEION na READ ena WRITE ina
 RANGE g, gbar
}

UNITS{
(mV) = (millivolt)
(S) = (siemens)
(mA)=(milliamp)
}

PARAMETER{
gbar=0.035 (S/cm2)
vshift=0 (mV)
}

ASSIGNED{
g (S/cm2)
v (mV)
ena(mV)
ina(mA/cm2)
o1c1 (/ms)
o1c2 (/ms)
i2c2 (/ms)
c1o1 (/ms)
c2o1 (/ms)
i1o1 (/ms)
i3o1 (/ms)
o1i1 (/ms)
i2i1 (/ms)
c2i2 (/ms)
i1i2 (/ms)
i3i2 (/ms)
o1i3 (/ms)
i2i3 (/ms)
}

STATE {c1 c2 o1 i1 i2 i3 }

BREAKPOINT {SOLVE kin METHOD sparse
g=gbar*o1
ina=g*(v-ena)
}

INITIAL {LOCAL sum
c1=1
c2 = exp(-4.1003000 + (-0.0065631*v))
o1 = exp(10.2360000 + (0.2838100*v))
i1 = exp(17.3810000 + (0.3142800*v))
i2 = exp(16.1780000 + (0.3672800*v))
i3 = exp(5.2305000 + (0.0897000*v))
sum = c1+c2+o1+i1+i2+i3
c1 = c1/sum
c2 = c2/sum
o1 = o1/sum
i1 = i1/sum
i2 = i2/sum
i3 = i3/sum
}

KINETIC kin {
rates(v)
~ c1<->o1 (c1o1, o1c1)
~ c2<->o1 (c2o1, o1c2)
~ o1<->i1 (o1i1, i1o1)
~ c2<->i2 (c2i2, i2c2)
~ i1<->i2 (i1i2, i2i1)
~ o1<->i3 (o1i3, i3o1)
~ i2<->i3 (i2i3, i3i2)
CONSERVE c1 + c2 + o1 + i1 + i2 + i3 =1
}

PROCEDURE rates(vm(mV)){
UNITSOFF
o1c1=exp(-5.0180000 + (vm*-0.1772490))
o1i3=exp(0.5123500 + (vm*0.0052635))
i2i3=exp(-3.6711500 + (vm*0.0436584))
c1o1=exp(5.2180000 + (vm*0.1065610))
i3o1=exp(14.8486500 + (vm*0.2956365))
i1o1=exp(-18.6755000 + (vm*-0.0000025))
c2o1=exp(2.1866650 + (vm*0.0443300))
o1i1=exp(-11.5305000 + (vm*0.0304675))
i2i1=exp(-1.5985000 + (vm*-0.0000000))
i3i2=exp(16.6071500 + (vm*0.4175016))
i1i2=exp(-2.8015000 + (vm*0.0530000))
c2i2=exp(6.8627500 + (vm*0.2200150))
o1c2=exp(-2.8188350 + (vm*-0.1497800))
i2c2=exp(-4.0847500 + (vm*-0.0575650))
UNITSON
}
