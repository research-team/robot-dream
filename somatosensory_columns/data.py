"""
Primal/initial dictionary of parts
It contains:
    -Motor Cortex
    -Striatum
    -GPe:       globus pallidus external
    -GPi:       globus pallidus internal
    -STN:       subthalamic nucleus
    -SNr:       substantia nigra pars reticulata
    -SNc:       substantia nigra pars compacta
    -Thalamus
    -Prefrontal cortex
    -NAc:       Nucleus Accumbens
    -VTA:       Ventral Tegmental Area
    -PPTg:      Pedunculopontine Tegmental nucleus
    -Amygdala
Prefix description:
    -GABA - GABA
    -Glu  - glutamate
    -ACh  - acetylcholine
    -DA   - dopamine
"""

from property import *

# Tuples of layers with Names and Numver of neurons
L2_tuple = ({k_name: 'L2 [Glu]'},
            {k_name: 'L2 [GABA]'})

L3_tuple = ({k_name: 'L3 [Glu]'},
            {k_name: 'L3 [GABA]'})

L4_tuple = ({k_name: 'L4 [Glu]'},
            {k_name: 'L4 [GABA]'})

L5A_tuple = ({k_name: 'L5A [Glu]'},
             {k_name: 'L5A [GABA]'})

L5B_tuple = ({k_name: 'L5B [Glu]'},
             {k_name: 'L5B [GABA]'})

L6_tuple = ({k_name: 'L6 [Glu]'},
            {k_name: 'L6 [GABA]'})

Striatum = ({k_name: 'Striatum'},)
Thalamus = ({k_name: 'Thalamus'},)
POm = ({k_name: 'Pom'},)

Cortex = (L2_tuple, L3_tuple, L4_tuple, L5A_tuple, L5B_tuple, L6_tuple)

Striatum[Glu][k_NN] = 100
Thalamus[Glu][k_NN] = 100
POm[Glu][k_NN] = 100

L2_tuple[Glu][k_NN] = 546
L2_tuple[GABA][k_NN] = 107

L3_tuple[Glu][k_NN] = 1145
L3_tuple[GABA][k_NN] = 123

L4_tuple[Glu][k_NN] = 1656
L4_tuple[GABA][k_NN] = 140

L5A_tuple[Glu][k_NN] = 454
L5A_tuple[GABA][k_NN] = 90

L5B_tuple[Glu][k_NN] = 641
L5B_tuple[GABA][k_NN] = 131

L6_tuple[Glu][k_NN] = 1288
L6_tuple[GABA][k_NN] = 127