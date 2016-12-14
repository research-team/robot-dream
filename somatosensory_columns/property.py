"""Main property"""
GlobalColumns = 30 #3000

X = 6
Y = 5

# keys for layer tuples
Glu = 0
GABA = 1

# Keys for synapse models
model = 0
basic_weight = 1

# additional keys for dict elements
L2, L3, L4, L5A, L5B,  L6 = range(6)

# Quality of graphics
dpi_n = 120

k_IDs = 'IDs'
k_name = 'Name'
k_NN = 'NN'
k_model = 'Model'

# general settings
T = 1000.
dt = 10.

# neurons number for spike detector
N_detect = 100

# Neurons number for multimeter
N_volt = 3

# Generator delay
pg_delay = 2.

# Synapse weights
w_Glu = 3.
w_GABA = -w_Glu * 2

# Minimal number of neurons
NN_minimal = 10

# Synapse models
glu_synapse      = 'glu_synapse'
gaba_synapse     = 'gaba_synapse'
gen_static_syn   = 'noise_conn'

# Additional setings
dopamine_flag = True     # dopamine modulation flag
status_gui = True        # True - GUI is on | False - is off
