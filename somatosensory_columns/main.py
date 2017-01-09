from functions import *

startbuild = datetime.datetime.now()
logger = logging.getLogger('neuromodulation')

logger.debug("* * * Building layers")
build_model(GlobalColumns)

# Initialize connections
logger.debug("* * * Connecting layers in columns")
for column in range(GlobalColumns):
    ''' L2 '''
    # for Glu
    connect(Cortex[L2][Glu][column],    Cortex[L2][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L2_to_L2)
    connect(Cortex[L2][Glu][column],    Cortex[L2][GABA][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L2_to_L2)
    connect(Cortex[L2][Glu][column],    Cortex[L3][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L2_to_L3)
    connect(Cortex[L2][Glu][column],    Cortex[L5A][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L2_to_L5A)
    connect(Cortex[L2][Glu][column],    Cortex[L5B][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L2_to_L5B)
    connect(Cortex[L2][Glu][column],    Striatum[Glu],              syn_type=Glu,   weight_coef=1.0)
    # for GABA
    connect(Cortex[L2][GABA][column],   Cortex[L2][Glu][column],    syn_type=GABA,  weight_coef=1.0)

    ''' L3 '''
    connect(Cortex[L3][Glu][column],    Cortex[L2][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L3_to_L2)
    connect(Cortex[L3][Glu][column],    Cortex[L3][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L3_to_L3)
    connect(Cortex[L3][Glu][column],    Cortex[L3][GABA][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L3_to_L3)
    connect(Cortex[L3][Glu][column],    Cortex[L5A][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L3_to_L5A)
    connect(Cortex[L3][Glu][column],    Cortex[L5B][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L3_to_L5B)
    connect(Cortex[L3][Glu][column],    Striatum[Glu],              syn_type=Glu,   weight_coef=1.0)
    # for GABA
    connect(Cortex[L3][GABA][column],   Cortex[L3][Glu][column],    syn_type=GABA,  weight_coef=1.0)

    ''' L4 '''
    # for Glu
    connect(Cortex[L4][Glu][column],    Cortex[L2][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L4_to_L2)
    connect(Cortex[L4][Glu][column],    Cortex[L3][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L4_to_L3)
    connect(Cortex[L4][Glu][column],    Cortex[L4][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L4_to_L4)
    connect(Cortex[L4][Glu][column],    Cortex[L4][GABA][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L4_to_L4)
    connect(Cortex[L4][Glu][column],    Cortex[L5A][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L4_to_L5A)
    connect(Cortex[L4][Glu][column],    Cortex[L5B][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L4_to_L5B)
    # for GABA
    connect(Cortex[L4][GABA][column],   Cortex[L4][Glu][column],    syn_type=GABA,  weight_coef=1.0)

    ''' L5A '''
    # for Glu
    connect(Cortex[L5A][Glu][column],   Cortex[L2][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L5A_to_L2)
    connect(Cortex[L5A][Glu][column],   Cortex[L3][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L5A_to_L3)
    connect(Cortex[L5A][Glu][column],   Cortex[L5A][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L5A_to_L5A)
    connect(Cortex[L5A][Glu][column],   Cortex[L5A][GABA][column],  syn_type=Glu,   weight_coef=1.0, conn_prob=L5A_to_L5A)
    connect(Cortex[L5A][Glu][column],   Cortex[L5B][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L5A_to_L5B)
    # for GABA
    connect(Cortex[L5A][GABA][column],  Cortex[L5A][Glu][column],   syn_type=GABA,  weight_coef=1.0)

    ''' L5B '''
    # for Glu
    connect(Cortex[L5B][Glu][column],   Cortex[L2][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L5B_to_L2)
    connect(Cortex[L5B][Glu][column],   Cortex[L3][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L5B_to_L3)
    connect(Cortex[L5B][Glu][column],   Cortex[L5B][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L5B_to_L5B)
    connect(Cortex[L5B][Glu][column],   Cortex[L5B][GABA][column],  syn_type=Glu,   weight_coef=1.0, conn_prob=L5B_to_L5B)
    connect(Cortex[L5B][Glu][column],   Cortex[L6][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L5B_to_L6)
    connect(Cortex[L5B][Glu][column],   Striatum[Glu],              syn_type=Glu,   weight_coef=1.0)
    connect(Cortex[L5B][Glu][column],   POm[Glu],                   syn_type=Glu,   weight_coef=1.0)
    # for GABA
    connect(Cortex[L5B][GABA][column],  Cortex[L5B][Glu][column],   syn_type=GABA,  weight_coef=1.0)

    ''' L6 '''
    # for Glu
    connect(Cortex[L6][Glu][column],    Cortex[L4][GABA][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L6_to_L4)
    connect(Cortex[L6][Glu][column],    Cortex[L5A][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L6_to_L5A)
    connect(Cortex[L6][Glu][column],    Cortex[L5B][Glu][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L6_to_L5B)
    connect(Cortex[L6][Glu][column],    Cortex[L6][Glu][column],    syn_type=Glu,   weight_coef=1.0, conn_prob=L6_to_L6)
    connect(Cortex[L6][Glu][column],    Cortex[L6][GABA][column],   syn_type=Glu,   weight_coef=1.0, conn_prob=L6_to_L6)
    connect(Cortex[L6][Glu][column],    Thalamus[Glu],              syn_type=Glu,   weight_coef=1.0)
    connect(Cortex[L6][Glu][column],    POm[Glu],                   syn_type=Glu,   weight_coef=1.0)
    # for GABA
    connect(Cortex[L6][GABA][column],  Cortex[L4][Glu][column],     syn_type=GABA,  weight_coef=1.0)
    connect(Cortex[L6][GABA][column],  Cortex[L6][Glu][column],     syn_type=GABA,  weight_coef=1.0)

    ''' POm '''
    connect(POm[Glu],       Cortex[L2][Glu][column],    syn_type=Glu,   weight_coef=1.0)

    ''' Thalamus '''
    connect(Thalamus[Glu],  Cortex[L3][Glu][column],    syn_type=Glu,   weight_coef=1.0)
    connect(Thalamus[Glu],  Cortex[L4][Glu][column],    syn_type=Glu,   weight_coef=1.0)
    connect(Thalamus[Glu],  Cortex[L5B][Glu][column],   syn_type=Glu,   weight_coef=1.0)
    connect(Thalamus[Glu],  Cortex[L6][Glu][column],    syn_type=Glu,   weight_coef=1.0)

logger.debug("* * * Adding neighbors connections")

for column in range(GlobalColumns):
    for neighbor in getNeighbors(column):
        # L2 layer
        connect(Cortex[L2][Glu][column],    Cortex[L2][Glu][neighbor],  syn_type=Glu,   weight_coef=0.5, conn_prob=L2_to_L2)
        # L3 layer
        connect(Cortex[L3][Glu][column],    Cortex[L3][Glu][neighbor],  syn_type=Glu,   weight_coef=0.5, conn_prob=L3_to_L3)
        # L5A layer
        connect(Cortex[L5A][Glu][column],   Cortex[L5A][Glu][neighbor], syn_type=Glu,   weight_coef=0.5, conn_prob=L5A_to_L5A)

logger.debug("* * * Connect generators")
specific_generator(Cortex[L6][Glu][2], coef_part=0.3)

logger.debug("* * * Connect detectors")

connect_detector(Thalamus[Glu])
setFlagToColumn(1)
setFlagToColumn(2)
setFlagToLayer(L5B)

del build_model, connect

endbuild = datetime.datetime.now()

simulate()
getFullDataOfColumn(1)
getFullDataOfColumn(2)
getMapOfLayer(L5B, 10) #in ms

get_log(startbuild, endbuild)
save(status_gui)
