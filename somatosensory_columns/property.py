"""Main property"""
X = 3
Y = 2
column_number = X * Y

# keys for layer tuples
Glu = 0
GABA = 1
k_param = 2
both = 2

# Keys for synapse models
model = 0
basic_weight = 1

# additional keys for dict elements
L2, L3, L4, L5A, L5B, L6 = range(6)

# Quality of graphics
dpi_n = 120

k_IDs = 'IDs'
k_name = 'Name'
k_NN = 'NN'
k_model = 'Model'

# general settings
T = 180.

# neurons number for spike detector
N_detect = 100

# Synapse
max_synapse = 600
min_synapse = 10

# Neurons number for multimeter
N_volt = 7

# Generator delay
pg_delay = 0.1

# Synapse weights
w_Glu = 70. #80
w_GABA = -w_Glu * 1.3

# Minimal number of neurons
NN_minimal = 10

image_format = 'png'
txtResultPath = 'txt'         # path for txt result
txtTimeSimulation = 'timeSimulation.txt'

# Additional setings
gui_flag = True
random_flag = False