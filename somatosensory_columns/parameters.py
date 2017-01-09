import nest
import numpy.random as random
from property import *

# E_L
L2_EL_mu = -79.3
L2_EL_sigma = 4.27 / 4

L3_EL_mu = -79.3
L3_EL_sigma = 4.27 / 4

L4_EL_mu = -71.8
L4_EL_sigma = 4.20 / 4

L5A_EL_mu = -69.9
L5A_EL_sigma = 4.18 / 4

L5B_EL_mu = -68.5
L5B_EL_sigma = 3.98 / 4

L6_EL_mu = -69.9
L6_EL_sigma = 4.18 / 4

# V_th
L2_Vth_mu = -49.5
L2_Vth_sigma = 3.81 / 4

L3_Vth_mu = -49.5
L3_Vth_sigma = 3.81 / 4

L4_Vth_mu = -48.7
L4_Vth_sigma = 3.53 / 4

L5A_Vth_mu = -49.7
L5A_Vth_sigma = 3.56 / 4

L5B_Vth_mu = -52.7
L5B_Vth_sigma = 3.59 / 4

L6_Vth_mu = -49.7
L6_Vth_sigma = 3.56 / 4

# C_m
L2_Cm_mu = 134.
L2_Cm_sigma = 32.8 / 4

L3_Cm_mu = 134.
L3_Cm_sigma = 32.8 / 4

L4_Cm_mu = 135.
L4_Cm_sigma = 36.7 / 4

L5A_Cm_mu = 133.
L5A_Cm_sigma = 31.9 / 4

L5B_Cm_mu = 284.
L5B_Cm_sigma = 78.5 / 4

L6_Cm_mu = 133.
L6_Cm_sigma = 31.9 / 4

# t_ref
L2_tref_mu = 1.3
L2_tref_sigma = 0.9 / 4

L3_tref_mu = 1.3
L3_tref_sigma = 0.9 / 4

L4_tref_mu = 1.8
L4_tref_sigma = 1.1 / 4

L5A_tref_mu = 2.7
L5A_tref_sigma = 1.7 / 4

L5B_tref_mu = 4.4
L5B_tref_sigma = 2.0 / 4

L6_tref_mu = 2.7
L6_tref_sigma = 1.7 / 4

# Connection probability
L2_to_L2    = 0.093
L2_to_L3    = 0.121
L2_to_L4    = 0.120
L2_to_L5A   = 0.043
L2_to_L5B   = 0.009

L3_to_L2    = 0.055
L3_to_L3    = 0.187
L3_to_L4    = 0.145
L3_to_L5A   = 0.022
L3_to_L5B   = 0.018

L4_to_L2    = 0.009
L4_to_L3    = 0.024
L4_to_L4    = 0.243
L4_to_L5A   = 0.007
L4_to_L5B   = 0.007

L5A_to_L2   = 0.095
L5A_to_L3   = 0.057
L5A_to_L4   = 0.116
L5A_to_L5A  = 0.191
L5A_to_L5B  = 0.017
L5A_to_L6   = 0.006

L5B_to_L2   = 0.083
L5B_to_L3   = 0.122
L5B_to_L4   = 0.081
L5B_to_L5A  = 0.080
L5B_to_L5B  = 0.072
L5B_to_L6   = 0.020

L6_to_L4    = 0.032
L6_to_L5A   = 0.032
L6_to_L5B   = 0.070
L6_to_L6    = 0.028

# Neuron parameters
global_neuron_parameters = {#'E_L': -70.,        # (mV) Resting membrane potential
                            #'V_th': -50.,       # (mV) Spike threshold
                            'V_reset': -67.,    # (mV) Reset membrane potential after a spike
                            #'C_m': 250.,        # (pF) Capacity of the membrane
                            #'t_ref': 2.,        # (ms) Duration of refractory period (V_m = V_reset)
                            'V_m': -60.,        # (mV) Membrane potential at start
                            #'tau_syn_ex': 1.,   # (ms) Time constant of postsynaptic excitatory currents
                            #'tau_syn_in': 1.
}   # (ms) Time constant of postsynaptic inhibitory currents

# L2P     L2 pyramidal cell
# L3P     L3 pyramidal cell
# L4SN    L4 spiny neuron -> pyramidal
# stL5P   slender-tufted L5A pyramidal cell
# ttL5BP  thick-tufted L5B pyramidal cell
# ctL6AP  corticothalamic L6A pyramidal cell

# Synapse common parameters
STDP_synapseparams = {
    'model': 'stdp_synapse',
    #'alpha': {'distribution': 'normal_clipped', 'low': 0.5, 'mu': 5.0, 'sigma': 1.0},
    'lambda': 0.5,      # Step size
    'alpha': 1.         # Asymmetry parameter (scales depressing increments as alpha*lambda)
}

# Glutamate synapse
STDP_synparams_Glu = dict({'delay': {'distribution': 'uniform', 'low': 1., 'high': 1.9},  # (ms) Distribution of delay values for connections
                           'weight': w_Glu}, **STDP_synapseparams) # (pA) Weight (power) of synapse
# GABA synapse
STDP_synparams_GABA = dict({'delay': {'distribution': 'uniform', 'low': 1., 'high': 1.9},
                            'weight': w_GABA}, **STDP_synapseparams)

# Dictionary of synapses with keys and their parameters
synapses = {Glu:   (STDP_synparams_Glu,    w_Glu),
            GABA:  (STDP_synparams_GABA,   w_GABA)}

# Parameters for generator


# Device parameters
multimeter_param = {'to_memory': True,
                    'to_file': False,
                    'withtime': True,
                    'interval': 0.1,
                    'record_from': ['V_m'],
                    'withgid': True}

detector_param = {'label': 'spikes',
                  'withtime': True,
                  'withgid': True,
                  'to_file': False,
                  'to_memory': True,
                  'scientific': True}