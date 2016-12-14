from func import *

startbuild = datetime.datetime.now()

nest.ResetKernel()
nest.SetKernelStatus({'overwrite_files': True,
                      'local_num_threads': 4,
                      'resolution': 0.1})
logger = logging.getLogger('neuromodulation')

logger.debug("* * * Building layers")

build_model(GlobalColumns)


# Init parameters of our synapse models
nest.CopyModel('static_synapse', gen_static_syn, static_syn)
nest.CopyModel('stdp_synapse', glu_synapse, STDP_synparams_Glu)
nest.CopyModel('stdp_synapse', gaba_synapse, STDP_synparams_GABA)

# Initialize connections
logger.debug("* * * Connecting layers in columns")

for column in range(GlobalColumns):
    ''' L2 '''
    # for Glu
    connect(Cortex[L2][Glu][column],    Cortex[L2][GABA][column],   syn_type=Glu,   weight_coef=0.3)    #0.3
    connect(Cortex[L2][Glu][column],    Cortex[L5][Glu][column],    syn_type=Glu,   weight_coef=0.3)

    # for GABA
    connect(Cortex[L2][GABA][column],   Cortex[L3][Glu][column],    syn_type=GABA, weight_coef=0.2)
    connect(Cortex[L2][GABA][column],   Cortex[L5][Glu][column],    syn_type=GABA, weight_coef=0.3)

    ''' L3 '''
    # for Glu
    connect(Cortex[L3][Glu][column],    Cortex[L2][Glu][column],    syn_type=Glu,   weight_coef=1.3)
    connect(Cortex[L3][Glu][column],    Cortex[L4][GABA][column],   syn_type=Glu,   weight_coef=0.1) #0/5

    ''' L4 '''
    # for Glu
    connect(Cortex[L4][Glu][column],    Cortex[L3][Glu][column],    syn_type=Glu,   weight_coef=0.9)
    #connect(Cortex[L4][Glu][column],    Cortex[L5][Glu][column],    syn_type=Glu,   weight_coef=0.3)
    connect(Cortex[L4][Glu][column],    Cortex[L4][GABA][column],   syn_type=Glu,   weight_coef=0.2)        #0.3
    # for GABA
    connect(Cortex[L4][GABA][column],  Cortex[L4][Glu][column],    syn_type=GABA,   weight_coef=0.2)        #0.2
    connect(Cortex[L4][GABA][column],  Cortex[L3][Glu][column],    syn_type=GABA,   weight_coef=0.1)        #0.3
    connect(Cortex[L4][GABA][column],  Cortex[L2][GABA][column],   syn_type=GABA,   weight_coef=0.3)

    ''' L5 '''
    # for Glu
    connect(Cortex[L5][Glu][column],    Cortex[L6][Glu][column],    syn_type=Glu,   weight_coef=0.1)
    connect(Cortex[L5][Glu][column],    Cortex[L5][GABA][column],   syn_type=Glu,   weight_coef=0.1)
    # for GABA
    connect(Cortex[L5][GABA][column],  Cortex[L5][GABA][column],   syn_type=GABA )

    ''' L6 '''
    # for Glu
    connect(Cortex[L6][Glu][column],    Cortex[L4][GABA][column],   syn_type=Glu,   weight_coef=0.2)    #0.3
    connect(Cortex[L6][Glu][column],    Cortex[L4][Glu][column],    syn_type=Glu,   weight_coef=0.3) ###0.4
    # for GABA
    connect(Cortex[L6][GABA][column],  Cortex[L6][Glu][column],    syn_type=GABA, weight_coef=0.4)


logger.debug("* * * Adding neighbors connections")

for column in range(X*Y):
    for neighbor in getNeighbors(column):
        # L2 layer
        # TO L3 !!!!!!
        connect(Cortex[L2][Glu][column],    Cortex[L3][Glu][neighbor],  syn_type=Glu,   weight_coef=0.1)
        connect(Cortex[L2][GABA][column],   Cortex[L2][GABA][neighbor], syn_type=Glu,   weight_coef=0.3)
        # L4 layer
        connect(Cortex[L4][Glu][column],    Cortex[L4][Glu][neighbor],  syn_type=Glu,   weight_coef=0.2)
        connect(Cortex[L4][GABA][column],   Cortex[L4][GABA][neighbor], syn_type=Glu,   weight_coef=0.3)

logger.debug("* * * Connect detectors")

connect_detectors()

connect_mm()

logger.debug("* * * Attaching spikes detectors")


logger.debug("* * * Attaching spikes detector")
for part in getAllParts():
    connect_detector(part)

logger.debug("* * * Attaching multimeters")
for part in getAllParts():
    connect_multimeter(part)



del build_model, connect

endbuild = datetime.datetime.now()

simulate()
get_log(startbuild, endbuild)
save(status_gui)
