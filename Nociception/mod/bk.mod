TITLE BK-type calcium activated K channel

UNITS {
    (molar) = (1/liter)
    (mV) = (millivolt)
    (mA) = (milliamp)
    (mM) = (millimolar)
    FARADAY = (faraday) (kilocoulombs)
    R = (k-mole) (joule/degC)
}

NEURON {
    SUFFIX bk
    USEION ca READ cai
    USEION k READ ek WRITE ik
    RANGE gbar, ik
}

PARAMETER {
    gbar = 0.0 (mho/cm2)
    k1 = 0.180 (mM)
    k4 = 0.011 (mM)
}

ASSIGNED {
    v (mV)
    ik (mA/cm2)
    celsius (degC)
    cai (mM) 
    ek (mV)
    oinf
    otau (ms)
}

STATE { o }

BREAKPOINT {
    SOLVE state METHOD cnexp
    ik = gbar*o*(v-ek)
}

DERIVATIVE state {
    rate(v, cai)
    o' = (oinf-o)/otau
}

INITIAL {
    rate(v, cai)
    o = oinf
}

PROCEDURE rate(v (mV), ca (mM)) {
    LOCAL a, b, sum, z
    UNITSOFF
    z = 1e-3*2*FARADAY/(R*(celsius+273.15))
    a = 0.48*ca/(ca+k1*exp(-0.84*z*v))
    b = 0.28/(1+ca/(k4*exp(-z*v)))
    sum = a+b
    oinf = a/sum
    otau = 1/sum
    UNITSON
}

COMMENT

Original model by Moczydlowski (1983), rat skeletal muscle.

Genesis implementation by De Schutter, adapted by Kai Du.

Revision by Evans (2012, 2013), K1 changed from 0.180 to 0.003 and K4
from 0.011 to 0.009, according to Berkefeld (2006), Xenopus oocytes.

NEURON implementation by Alexander Kozlov <akozlov@csc.kth.se>.

ENDCOMMENT
