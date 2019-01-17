COMMENT
State-dependent Na channel model exhibiting only fast inactivation
Menon V, Spruston N, Kath WL, 2009
ENDCOMMENT

NEURON{
SUFFIX nafast
USEION na READ ena WRITE ina
 RANGE g, gbar, ina
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
i1c2 (/ms)
c1o1 (/ms)
c2o1 (/ms)
i2o1 (/ms)
c2i1 (/ms)
i2i1 (/ms)
o1i2 (/ms)
i1i2 (/ms)
}

STATE {c1 c2 o1 i1 i2 }

BREAKPOINT {SOLVE kin METHOD sparse
g=gbar*o1
ina=g*(v-ena)
}

INITIAL {LOCAL sum
c1=1
UNITSOFF
c2 = exp(-4.1003000 + (-0.0073075*v))
o1 = exp(10.2360000 + (0.2838100*v))
i1 = exp(16.1780000 + (0.3672800*v))
i2 = exp(5.3091536 + (0.0897000*v))
UNITSON
sum = c1+c2+o1+i1+i2
c1 = c1/sum
c2 = c2/sum
o1 = o1/sum
i1 = i1/sum
i2 = i2/sum
}

KINETIC kin {
rates(v)
~ c1<->o1 (c1o1, o1c1)
~ c2<->o1 (c2o1, o1c2)
~ c2<->i1 (c2i1, i1c2)
~ o1<->i2 (o1i2, i2o1)
~ i1<->i2 (i1i2, i2i1)
CONSERVE c1 + c2 + o1 + i1 + i2 =1
}

PROCEDURE rates(vm(mV)){
UNITSOFF
o1c1=exp(-5.0180000 + (vm*-0.1772490))
o1c2=exp(0.5123500 + (vm*0.0048913))
i1c2=exp(-3.6711500 + (vm*0.0661184))
c1o1=exp(5.2180000 + (vm*0.1065610))
c2o1=exp(14.8486500 + (vm*0.2960088))
i2o1=exp(2.1473382 + (vm*0.0443300))
c2i1=exp(16.6071500 + (vm*0.4407059))
i2i1=exp(5.4979573 + (vm*0.2200150))
o1i2=exp(-2.7795082 + (vm*-0.1497800))
i1i2=exp(-5.3708892 + (vm*-0.0575650))
UNITSON
}
