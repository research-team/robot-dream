"""Main property"""


X = 3
Y = 2

GlobalColumns = X * Y

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
T = 500.
dt = 10.

# neurons number for spike detector
N_detect = 100

# Neurons number for multimeter
N_volt = 7

# Generator delay
pg_delay = 2.

# Synapse weights
w_Glu = 20.
w_GABA = -w_Glu * 1.5

# Minimal number of neurons
NN_minimal = 10

# Additional setings
status_gui = True        # True - GUI is on | False - is off