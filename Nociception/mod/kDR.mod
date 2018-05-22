TITLE  Non-inactivating potassium delayed rectifier current (kDR-current)

COMMENT
written for NEURON by Antonios Dougalis, 23 Feb 2015, London
based on voltage clamp data from Dougalis et al., 2017 J Compu Neurosci 
ENDCOMMENT

UNITS {
        (S) = (siemens)
        (mA) = (milliamp)
        (mV) = (millivolt)
}
 
NEURON {
        SUFFIX kdr
        USEION k READ ek WRITE ik
		RANGE gkDRbar,ikDR,ik,ek
        RANGE ninf
		RANGE tau_n
		RANGE vhalfkDRAct,slopekDRAct, vhalfkDRTAct, slopekDRTAct
}
 
PARAMETER {
        v   (mV)
        dt  (ms)
		gkDRbar = 0.003 (S/cm2)
        ek  = -73.0  (mV)
		vhalfkDRAct = -25 (mV)
        slopekDRAct = 12
        vhalfkDRTAct = -38.4 (mV)
        slopekDRTAct = -6.9	
}
 
STATE {
        n
}
 
ASSIGNED {
        ik (mA/cm2)
		ikDR (mA/cm2)
        ninf 
	    tau_n
}
 
BREAKPOINT {
        SOLVE states METHOD cnexp
        ikDR = gkDRbar*n*n*(v - ek)      
        ik=ikDR		
}
 
UNITSOFF

INITIAL {
        n = ninf
        
 }

DERIVATIVE states { 
        LOCAL ninf,tau_n
        ninf = 1/(1 + exp(-(v - vhalfkDRAct)/slopekDRAct))
		tau_n = 95.2* (1/(1 + exp(-(v - vhalfkDRTAct)/slopekDRTAct))) 
		n' = (ninf-n)/tau_n
		
}
 
UNITSON
