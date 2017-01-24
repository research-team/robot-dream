from functions import *

g.startbuild = datetime.datetime.now()
logger = logging.getLogger('neuromodulation')

logger.debug("* * * Building layers")
build_model()

logger.debug("* * * Connecting layers in columns")
for column in range(column_number):
    print "COLUMN {0}".format(column)
    ''' L2 '''
    # for Glu
    connect(Cortex[L2][column][Glu], Cortex[L2][column][Glu],  neurotransmitter=Glu, weight_coef=0.7, conn_prob=L2_to_L2)
    connect(Cortex[L2][column][Glu], Cortex[L2][column][GABA], neurotransmitter=Glu, weight_coef=0.5, conn_prob=L2_to_L2)
    connect(Cortex[L2][column][Glu], Cortex[L3][column][Glu],  neurotransmitter=Glu, weight_coef=1.0, conn_prob=L2_to_L3)
    connect(Cortex[L2][column][Glu], Cortex[L5A][column][Glu], neurotransmitter=Glu, weight_coef=1.0, conn_prob=L2_to_L5A)
    connect(Cortex[L2][column][Glu], Cortex[L5B][column][Glu], neurotransmitter=Glu, weight_coef=1.0, conn_prob=L2_to_L5B)
    # for GABA
    connect(Cortex[L2][column][GABA], Cortex[L2][column][Glu], neurotransmitter=GABA, weight_coef=1.5)

    ''' L3 '''
    #connect(Cortex[L3][column][Glu], Cortex[L2][column][Glu],  neurotransmitter=Glu, weight_coef=1.0, conn_prob=L3_to_L2)
    connect(Cortex[L3][column][Glu], Cortex[L3][column][Glu],  neurotransmitter=Glu, weight_coef=0.7, conn_prob=L3_to_L3)
    connect(Cortex[L3][column][Glu], Cortex[L3][column][GABA], neurotransmitter=Glu, weight_coef=0.5, conn_prob=L3_to_L3)
    connect(Cortex[L3][column][Glu], Cortex[L5A][column][Glu], neurotransmitter=Glu, weight_coef=1.0, conn_prob=L3_to_L5A)
    #connect(Cortex[L3][column][Glu], Cortex[L5B][column][Glu], neurotransmitter=Glu, weight_coef=1.0, conn_prob=L3_to_L5B)
    # for GABA
    connect(Cortex[L3][column][GABA], Cortex[L3][column][Glu], neurotransmitter=GABA, weight_coef=1.5)

    ''' L4 '''
    # for Glu
    connect(Cortex[L4][column][Glu], Cortex[L2][column][Glu],  neurotransmitter=Glu, weight_coef=0.6, conn_prob=L4_to_L2)
    connect(Cortex[L4][column][Glu], Cortex[L3][column][Glu],  neurotransmitter=Glu, weight_coef=0.6, conn_prob=L4_to_L3)
    connect(Cortex[L4][column][Glu], Cortex[L4][column][Glu],  neurotransmitter=Glu, weight_coef=0.7, conn_prob=L4_to_L4)
    connect(Cortex[L4][column][Glu], Cortex[L4][column][GABA], neurotransmitter=Glu, weight_coef=0.5, conn_prob=L4_to_L4)
    connect(Cortex[L4][column][Glu], Cortex[L5A][column][Glu], neurotransmitter=Glu, weight_coef=0.6, conn_prob=L4_to_L5A)
    connect(Cortex[L4][column][Glu], Cortex[L5B][column][Glu], neurotransmitter=Glu, weight_coef=0.6, conn_prob=L4_to_L5B)
    # for GABA
    connect(Cortex[L4][column][GABA], Cortex[L4][column][Glu], neurotransmitter=GABA, weight_coef=1.5)

    ''' L5A '''
    # for Glu
    connect(Cortex[L5A][column][Glu], Cortex[L2][column][Glu],   neurotransmitter=Glu, weight_coef=1.0, conn_prob=L5A_to_L2)
    connect(Cortex[L5A][column][Glu], Cortex[L3][column][Glu],   neurotransmitter=Glu, weight_coef=1.0, conn_prob=L5A_to_L3)
    connect(Cortex[L5A][column][Glu], Cortex[L4][column][Glu],   neurotransmitter=Glu, weight_coef=0.5, conn_prob=L5A_to_L4)
    connect(Cortex[L5A][column][Glu], Cortex[L5A][column][Glu],  neurotransmitter=Glu, weight_coef=0.7, conn_prob=L5A_to_L5A)
    connect(Cortex[L5A][column][Glu], Cortex[L5A][column][GABA], neurotransmitter=Glu, weight_coef=0.5, conn_prob=L5A_to_L5A)
    #connect(Cortex[L5A][column][Glu], Cortex[L5B][column][Glu],  neurotransmitter=Glu, weight_coef=1.0, conn_prob=L5A_to_L5B)
    connect(Cortex[L5A][column][Glu], Cortex[L6][column][Glu],  neurotransmitter=Glu, weight_coef=1.0, conn_prob=L5A_to_L6)
    # for GABA
    connect(Cortex[L5A][column][GABA], Cortex[L5A][column][Glu], neurotransmitter=GABA, weight_coef=1.5)

    ''' L5B '''
    # for Glu
    connect(Cortex[L5B][column][Glu], Cortex[L2][column][Glu],   neurotransmitter=Glu, weight_coef=1.0, conn_prob=L5B_to_L2)
    connect(Cortex[L5B][column][Glu], Cortex[L3][column][Glu],   neurotransmitter=Glu, weight_coef=1.0, conn_prob=L5B_to_L3)
    connect(Cortex[L5B][column][Glu], Cortex[L4][column][Glu],   neurotransmitter=Glu, weight_coef=0.8, conn_prob=L5B_to_L4)
    connect(Cortex[L5B][column][Glu], Cortex[L5B][column][Glu],  neurotransmitter=Glu, weight_coef=0.7, conn_prob=L5B_to_L5B)
    connect(Cortex[L5B][column][Glu], Cortex[L5B][column][GABA], neurotransmitter=Glu, weight_coef=0.5, conn_prob=L5B_to_L5B)
    #connect(Cortex[L5B][column][Glu], Cortex[L6][column][Glu],   neurotransmitter=Glu, weight_coef=1.0, conn_prob=L5B_to_L6)
    # for GABA
    connect(Cortex[L5B][column][GABA], Cortex[L5B][column][Glu], neurotransmitter=GABA, weight_coef=1.5)

    ''' L6 '''
    # for Glu
    connect(Cortex[L6][column][Glu], Cortex[L4][column][Glu], neurotransmitter=Glu, weight_coef=0.7, conn_prob=L6_to_L4)
    connect(Cortex[L6][column][Glu], Cortex[L5A][column][Glu], neurotransmitter=Glu, weight_coef=1.0, conn_prob=L6_to_L5A)
    connect(Cortex[L6][column][Glu], Cortex[L5B][column][Glu], neurotransmitter=Glu, weight_coef=1.0, conn_prob=L6_to_L5B)
    connect(Cortex[L6][column][Glu], Cortex[L6][column][Glu],  neurotransmitter=Glu, weight_coef=0.7, conn_prob=L6_to_L6)
    connect(Cortex[L6][column][Glu], Cortex[L6][column][GABA], neurotransmitter=Glu, weight_coef=0.5, conn_prob=L6_to_L6)
    # for GABA
    connect(Cortex[L6][column][GABA], Cortex[L4][column][Glu], neurotransmitter=GABA, weight_coef=1.5)
    connect(Cortex[L6][column][GABA], Cortex[L6][column][Glu], neurotransmitter=GABA, weight_coef=1.5)

logger.debug("* * * Adding neighbors connections")
for column in range(column_number):
    for neighbor in neighbors[column]:
        # L2 layer
        connect(Cortex[L2][column][Glu], Cortex[L2][neighbor][Glu], neurotransmitter=Glu, weight_coef=0.5, conn_prob=L2_to_L2)
        # L3 layer
        #connect(Cortex[L3][column][Glu],    Cortex[L3][neighbor][Glu],  syn_type=Glu,   weight_coef=1.0, conn_prob=L3_to_L3)
        # L5A layer
        connect(Cortex[L5A][column][Glu], Cortex[L5A][neighbor][Glu], neurotransmitter=Glu, weight_coef=0.5, conn_prob=L5A_to_L5A)

logger.debug("* * * Connect generators")
specific_generator(Cortex[L6][2][Glu], coef_part=0.3)

logger.debug("* * * Connect detectors")
set_flag_to_column(2, neurotransmitter=both, heatmap=True, multimeter=True)
set_flag_to_layer(L5A, neurotransmitter=both, heatmap=True, multimeter=False)

logger.debug("* * * Add wafe")
big_wave(rate_HZ=20, percent=100)

g.endbuild = datetime.datetime.now()

simulate()

log()
save()