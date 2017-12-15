TITLE Calcium T channel for Subthalamic Nucleus

UNITS {
    (mV) = (millivolt)
    (mA) = (milliamp)
}

NEURON {
    SUFFIX cat
    USEION ca READ eca WRITE ica
    RANGE gmax
}

PARAMETER {
    gmax  = 0.002 (mho/cm2)
}

ASSIGNED { 
    v (mV)
    eca (mV)
    ica (mA/cm2)
    ralpha (/ms)
    rbeta (/ms)
    salpha (/ms)
    sbeta (/ms)
    dalpha (/ms)
    dbeta (/ms)
}

STATE {
    r s d
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ica  = gmax*r*r*r*s*(v-eca)
}

INITIAL {
    settables(v)
    r = ralpha/(ralpha+rbeta)
    s = (salpha*(dbeta+dalpha) - (salpha*dbeta))/
              ((salpha+sbeta)*(dalpha+dbeta) - (salpha*dbeta))
    d = (dbeta*(salpha+sbeta) - (salpha*dbeta))/
              ((salpha+sbeta)*(dalpha+dbeta) - (salpha*dbeta))
}

DERIVATIVE states {  
    settables(v)      
    r' = ((ralpha*(1-r)) - (rbeta*r))
    d' = ((dbeta*(1-s-d)) - (dalpha*d))
    s' = ((salpha*(1-s-d)) - (sbeta*s))
}

UNITSOFF

PROCEDURE settables(v (mV)) {
    LOCAL  bd
    TABLE ralpha, rbeta, salpha, sbeta, dalpha, dbeta 
          FROM -100 TO 100 WITH 200

    ralpha = 1.0/(1.7+exp(-(v+28.2)/13.5))
    rbeta  = exp(-(v+63.0)/7.8)/(exp(-(v+28.8)/13.1)+1.7)

    salpha = exp(-(v+160.3)/17.8)
    sbeta  = (sqrt(0.25+exp((v+83.5)/6.3))-0.5) * 
                     (exp(-(v+160.3)/17.8))

    bd     = sqrt(0.25+exp((v+83.5)/6.3))
    dalpha = (1.0+exp((v+37.4)/30.0))/(240.0*(0.5+bd))
    dbeta  = (bd-0.5)*dalpha
}

UNITSON