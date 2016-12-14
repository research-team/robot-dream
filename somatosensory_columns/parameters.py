import nest
import numpy.random as random
from property import *

# E_L
L2_EL_mu = -79.3
L2_EL_sigma = 4.27

L3_EL_mu = -79.3
L3_EL_sigma = 4.27

L4_EL_mu = -71.8
L4_EL_sigma = 4.20

L5A_EL_mu = -69.9
L5A_EL_sigma = 4.18

L5B_EL_mu = -68.5
L5B_EL_sigma = 3.98

L6_EL_mu = -69.9
L6_EL_sigma = 4.18

# V_th
L2_Vth_mu = -49.5
L2_Vth_sigma = 3.81

L3_Vth_mu = -49.5
L3_Vth_sigma = 3.81

L4_Vth_mu = -48.7
L4_Vth_sigma = 3.53

L5A_Vth_mu = -49.7
L5A_Vth_sigma = 3.56

L5B_Vth_mu = -52.7
L5B_Vth_sigma = 3.59

L6_Vth_mu = -49.7
L6_Vth_sigma = 3.56

# C_m
L2_Cm_mu = 134
L2_Cm_sigma = 32.8

L3_Cm_mu = 134
L3_Cm_sigma = 32.8

L4_Cm_mu = 135
L4_Cm_sigma = 367

L5A_Cm_mu = 133
L5A_Cm_sigma = 319

L5B_Cm_mu = 284
L5B_Cm_sigma = 78.5

L6_Cm_mu = 133
L6_Cm_sigma = 319

# t_ref
L2_tref_mu = 1.3
L2_tref_sigma = 0.9

L3_tref_mu = 1.3
L3_tref_sigma = 0.9

L4_tref_mu = 1.8
L4_tref_sigma = 1.1

L5A_tref_mu = 2.7
L5A_tref_sigma = 1.7

L5B_tref_mu = 4.4
L5B_tref_sigma = 2.0

L6_tref_mu = 2.7
L6_tref_sigma = 1.7


# Neuron parameters
global_neuron_parameters = {'E_L': -70.,  # (mV) Resting membrane potential
                            'V_th': -50.,  # (mV) Spike threshold
                            'V_reset': -67.,  # (mV) Reset membrane potential after a spike
                            'C_m': 250.,  # (pF) Capacity of the membrane
                            't_ref': 2.,  # (ms) Duration of refractory period (V_m = V_reset)
                            'V_m': -60.,  # (mV) Membrane potential at start
                            'tau_syn_ex': 1.,  # (ms) Time constant of postsynaptic excitatory currents
                            'tau_syn_in': 1.}     # (ms) Time constant of postsynaptic inhibitory currents

# L2P     L2 pyramidal cell
# L3P     L3 pyramidal cell
# L4SN    L4 spiny neuron -> pyramidal
# stL5P   slender-tufted L5A pyramidal cell
# ttL5BP  thick-tufted L5B pyramidal cell
# ctL6AP  corticothalamic L6A pyramidal cell

L2_pyr = dict(dict(E_L=     {'distribution': 'normal',  'mu': L2_EL_mu,     'sigma': L2_EL_sigma},
                   V_th=    {'distribution': 'normal',  'mu': L2_Vth_mu,    'sigma': L2_Vth_sigma},
                   C_m=     {'distribution': 'normal',  'mu': L2_Cm_mu,     'sigma': L2_Cm_sigma},
                   t_ref=   {'distribution': 'normal',  'mu': L2_tref_mu,   'sigma': L2_tref_sigma}), **global_neuron_parameters)

L3_pyr = dict(dict(E_L=     {'distribution': 'normal',  'mu': L3_EL_mu,     'sigma': L3_EL_sigma},
                   V_th=    {'distribution': 'normal',  'mu': L3_Vth_mu,    'sigma': L3_Vth_sigma},
                   C_m=     {'distribution': 'normal',  'mu': L3_Cm_mu,     'sigma': L3_Cm_sigma},
                   t_ref=   {'distribution': 'normal',  'mu': L3_tref_mu,   'sigma': L3_tref_sigma}), **global_neuron_parameters)

L4_pyr = dict(dict(E_L=     {'distribution': 'normal',  'mu': L4_EL_mu,     'sigma': L4_EL_sigma},
                   V_th=    {'distribution': 'normal',  'mu': L4_Vth_mu,    'sigma': L4_Vth_mu},
                   C_m=     {'distribution': 'normal',  'mu': L4_Cm_mu,     'sigma': L4_Cm_sigma},
                   t_ref=   {'distribution': 'normal',  'mu': L4_tref_mu,   'sigma': L4_tref_sigma}), **global_neuron_parameters)

L5A_pyr = dict(dict(E_L=    {'distribution': 'normal',  'mu': L5A_EL_mu,    'sigma': L5A_EL_sigma},
                    V_th=   {'distribution': 'normal',  'mu': L5A_Vth_mu,   'sigma': L5A_Vth_sigma},
                    C_m=    {'distribution': 'normal',  'mu': L5A_Cm_mu,    'sigma': L5A_Cm_sigma},
                    t_ref=  {'distribution': 'normal',  'mu': L5A_tref_mu,  'sigma': L5A_tref_sigma}), **global_neuron_parameters)

L5B_pyr = dict(dict(E_L=    {'distribution': 'normal',  'mu': L5B_EL_mu,    'sigma': L5B_EL_sigma},
                    V_th=   {'distribution': 'normal',  'mu': L5B_Vth_mu,   'sigma': L5B_Vth_sigma},
                    C_m=    {'distribution': 'normal',  'mu': L5B_Cm_mu,    'sigma': L5B_Cm_sigma},
                    t_ref=  {'distribution': 'normal',  'mu': L5B_tref_mu,  'sigma': L5B_tref_sigma}), **global_neuron_parameters)

L6_pyr = dict(dict(E_L=     {'distribution': 'normal',  'mu': L6_EL_mu,     'sigma': L6_EL_sigma},
                   V_th=    {'distribution': 'normal',  'mu': L6_Vth_mu,    'sigma': L6_Vth_sigma},
                   C_m=     {'distribution': 'normal',  'mu': L6_Cm_mu,     'sigma': L6_Cm_sigma},
                   t_ref=   {'distribution': 'normal',  'mu': L6_tref_mu,   'sigma': L6_tref_sigma}), **global_neuron_parameters)

# Synapse common parameters
STDP_synapseparams = {
    'alpha': random.normal(0.5, 5.0),       # Asymmetry parameter (scales depressing increments as alpha*lambda)
    'lambda': 0.5                           # Step size
}

# Glutamate synapse
STDP_synparams_Glu = dict({'delay': {'distribution': 'normal', 'mu': 1.0, 'sigma': 0.3},  # (ms) Distribution of delay values for connections
                           'weight': w_Glu}, **STDP_synapseparams) # (pA) Weight (power) of synapse
# GABA synapse
STDP_synparams_GABA = dict({'delay': {'distribution': 'normal', 'mu': 1.0, 'sigma': 0.3},
                            'weight': w_GABA}, **STDP_synapseparams)

# Dictionary of synapses with keys and their parameters
synapses = {Glu:   (glu_synapse,     w_Glu  ),
            GABA:  (gaba_synapse,    w_GABA ),
            ACh:   (ach_synapse,     w_ACh  ),
            DA_ex: (dopa_synapse_ex, w_DA_ex),
            DA_in: (dopa_synapse_in, w_DA_in)
}

# Parameters for generator
static_syn = {
    'weight': w_Glu * 5,
    'delay': pg_delay
}

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


