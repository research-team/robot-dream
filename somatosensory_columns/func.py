import os
import sys
import nest
import time
import logging
import datetime
import numpy as np
import nest.topology as tp
import matplotlib.pyplot as plt
from collections import defaultdict
from parameters import *
from time import clock
from data import *

neighbors = {}
dictPosition_NeuronID = {}  # position (1,0,1) : 6 neuron ID
spike_generators = {}       # dict name_part : spikegenerator
spike_detectors = {}         # dict name_part : spikedetector
multimeters = {}         # dict name_part : spikedetector
txtResultPath = ""          # path for txt result
MaxSynapses = 10      # max synapses
startsimulate = 0           # begin of simulation
endsimulate = 0             # end of simulation
SAVE_PATH = ""              # path to save results
SYNAPSES = 0                # number of synapses
NEURONS = 0                 # number of neurons
times = []                  # list for writing time simulation

FORMAT = '%(name)s.%(levelname)s: %(message)s.'
logging.basicConfig(format=FORMAT, level=logging.DEBUG)
logger = logging.getLogger('function')
import ast
def connect(pre, post, syn_type=GABA, weight_coef=1):
    print pre
    print post
    if type(pre) is dict:
        if k_IDs in pre:
            pre = tuple(pre[k_IDs])
        else:
            pre = ast.literal_eval(str(pre.values()[:GlobalColumns]).replace("(", "").replace(")", ""))
    if type(post) is dict:
        if k_IDs in post:
            post = tuple(post[k_IDs])
        else:
            post = ast.literal_eval(str(post.values()[:GlobalColumns]).replace("(", "").replace(")", ""))
    global SYNAPSES

    # Set new weight value (weight_coef * basic weight)
    nest.SetDefaults(synapses[syn_type][model], {'weight': weight_coef * synapses[syn_type][basic_weight]})
    # Create dictionary of connection rules
    conn_dict = {'rule': 'fixed_outdegree',
                 'outdegree': MaxSynapses if len(post) > MaxSynapses else len(post),
                 'multapses': False}
    # Connect PRE IDs neurons with POST IDs neurons, add Connection and Synapse specification
    nest.Connect(pre, post, conn_spec=conn_dict, syn_spec=synapses[syn_type][model])
    # Show data of new connection
    logger.debug("Connect {0} to {1} ({2}) +w {3}".format(pre, post, synapses[syn_type][model],  nest.GetDefaults(synapses[syn_type][model])['weight']))

def getNeighbors(column):
    return neighbors[column]

def build_model(column_number):
    global NEURONS, neighbors
    nest.SetDefaults('iaf_psc_exp', iaf_neuronparams)
    for layer in Cortex:
        for mediator in layer:
            for column in range(column_number):
                mediator[column] = nest.Create("iaf_psc_exp", mediator[k_NN])
                NEURONS += mediator[k_NN]

    logger.debug("* * * Creating MAP")
    # build MAP
    matrix2D = [ i for i in range(X*Y) ]
    print matrix2D
    neighbors = {}
    size = X*Y
    print np.arange(X * Y).reshape(Y, X)
    for y in range(Y):
        for x in range(X):
            current = y * X + x
            neighbors[current] = list()
            proxy = neighbors[current]
            right = left = top = bottom = False
            if current + 1 < X * (y+1):
                proxy.append(current+1)
                right = True
            if current - 1 >= y*X:
                proxy.append(current-1)
                left = True
            if current + X < size:
                proxy.append(current + X)
                bottom = True
            if current - X >= 0:
                proxy.append(current - X)
                top = True
            if top:
                if right:
                    proxy.append(current - X + 1)
                if left:
                    proxy.append(current - X - 1)
            if bottom:
                if right:
                    proxy.append(current + X + 1)
                if left:
                    proxy.append(current + X - 1)


def generate_neurons(NNumber):
    global NEURONS, all_parts
    logger.debug("* * * Start generate neurons")

    parts_no_dopa = gpe + gpi + stn + amygdala + (vta[vta_GABA0], vta[vta_GABA1], vta[vta_GABA2], snc[snc_GABA]) + \
                    striatum + prefrontal + nac + pptg + thalamus + snr
    parts_with_dopa = (vta[vta_DA0], vta[vta_DA1], snc[snc_DA])

    all_parts = tuple(sorted(parts_no_dopa + parts_with_dopa))

    NN_coef = float(NNumber) / sum(item[k_NN] for item in all_parts)

    for part in all_parts:
        part[k_NN] = NN_minimal if int(part[k_NN] * NN_coef) < NN_minimal else int(part[k_NN] * NN_coef)
    NEURONS = sum(item[k_NN] for item in all_parts)

    logger.debug('Initialized: {0} neurons'.format(NEURONS))

    # Init neuron models with our parameters
    nest.SetDefaults('iaf_psc_exp',   iaf_neuronparams)
    nest.SetDefaults('iaf_psc_alpha', iaf_neuronparams)

    # Parts without dopamine
    for part in parts_no_dopa:
        part[k_model] = 'iaf_psc_exp'
    # Parts with dopamine
    for part in parts_with_dopa:
        part[k_model] = 'iaf_psc_alpha'
    # Creating neurons
    for part in all_parts:
        part[k_IDs] = nest.Create(part[k_model], part[k_NN])
        logger.debug("{0} [{1}, {2}] {3} neurons".format(part[k_name], part[k_IDs][0], part[k_IDs][-1:][0], part[k_NN]))

def connect_generator(part, startTime=1, stopTime=T, rate=250, coef_part=1):
    name = part[k_name]
    # Add to spikeGenerators dict a new generator
    spike_generators[name] = nest.Create('poisson_generator', 1, {'rate' : float(rate),
                                                                  'start': float(startTime),
                                                                  'stop' : float(stopTime)})
    # Create dictionary of connection rules
    conn_dict = {'rule': 'fixed_outdegree',
                 'outdegree': int(part[k_NN] * coef_part)}
    # Connect generator and part IDs with connection specification and synapse specification
    nest.Connect(spike_generators[name], part[k_IDs], conn_spec=conn_dict, syn_spec=static_syn)
    # Show data of new generator
    logger.debug("Generator => {0}. Element #{1}".format(name, spike_generators[name][0]))


def connect_detector(part):
    name = part[k_name]
    # Init number of neurons which will be under detector watching
    number = part[k_NN] if part[k_NN] < N_detect else N_detect
    # Add to spikeDetectors a new detector
    spike_detectors[name] = nest.Create('spike_detector', params=detector_param)
    # Connect N first neurons ID of part with detector
    nest.Connect(part[k_IDs][:number], spike_detectors[name])
    # Show data of new detector
    logger.debug("Detector => {0}. Tracing {1} neurons".format(name, number))


def connect_detectors():
    for column in range(X * Y):
        detect  = nest.Create('spike_detector', params=detector_param)
        spike_detectors[column] = detect
        nest.Connect(Cortex[L6][L6_Glu][column], detect)
        logger.debug("Detector => {0}. Tracing {1} neurons".format(column, Cortex[L4][L4_Glu][column]))

def connect_mm():
    for column in range(X * Y):
        mm = nest.Create('multimeter', params=multimeter_param)
        multimeters[column] = mm
        nest.Connect(mm, (Cortex[L4][L4_Glu][column][:]))
        logger.debug("MM => {0}. Tracing {1} neurons".format(column, Cortex[L4][L4_Glu][column]))

def connect_multimeter(part):
    name = part[k_name]
    multimeters[name] = nest.Create('multimeter', params=multimeter_param)  # ToDo add count of multimeters
    nest.Connect(multimeters[name], part[k_IDs][4:9:1])
    logger.debug("Multimeter => {0}. On {1}".format(name, part[k_IDs][:N_volt]))



from multiprocessing import Process
from time import sleep


def getAllParts():
    return all_parts

def simulate():
    global startsimulate, endsimulate, SAVE_PATH
    logger.debug('* * * Simulating')
    startsimulate = datetime.datetime.now()
    import time
    raw = "1300 1600 1600 3250 2500 2900 3100 2700 3350 1400 1550 1600 1500 1550 1650 1650 1700 1450 2900 2850 3250 3000 2700 2750 1700 1700 1650 1700 1550 1700 1650 1700 1500 1700 1650 1650 2750 3100 3000 2950 2950 3000 3100 3100 3250 3100 1200 1450 1450 1400 1550 1650 1700 1600 1700 1650 1450 1650 1600 1550 1400 1700 3100 3200 3400 3100 3100 3000 2950 1400 1350 1250 1250 1250 1250 1000 1150 1300 1300 1250 1250 1250 1300 1250 1250 1000 3050 2950 3100 3150 3000 3350 3100 3000 2950 1100 1500 1550 1500 1500 1350 1350 1400 1400 1350 1400 1250 1300 1350 1200 1400 1250 1400 1400 1300 1400 1400 1400 1400 1200 1300 1300 1200 1400 1100 1400 1400 1200 1300 1300 1200 1400 1400 1400 1400 1400 1400 1350 1400 1250 1300 1200 1400 1250 1200 1300 1400 1400 1400 1350 1350 1350 1150 1350 1400 1250 1150 1200 1400 1350 1400 1300 1400 2750 3100 2950 2700 2400 2050 2300 2300 2300 2150 2300 2300 2400 2050 2200 2300 2300 2300 2300 2400 2200 2150 2300 2250 2000 2200 2250 1950 2100 2100 2200 2200 2100 2300 2150 2200 1950 2100 1800 2750 2600 2850 2650 2750 2750 2600 2750 2600 2750 2850 2850 2500 2850 2800 2300 2600 2750 2450 2450 2750 2450 2750 2750 2850 2600 2600 2450 2750 1450 3150 3200 3450 2800 3050 3050 3400 3250 3100"
    intervals = raw.split(" ")
    spikes = [0.0]
    for i in range(len(intervals)):
        spikes.append( float( "%.1f" % (spikes[i] + float(intervals[i]) / 1000) ) )

    print intervals
    print spikes
    # =================
    generator1 = nest.Create('spike_generator', 1)
    nest.SetStatus(generator1, {'spike_times': spikes[1:], 'spike_weights': [100. for i in spikes[1:]]})
    nest.Connect(generator1, Cortex[L6][L6_Glu][10][6:11:1])
    # ================
    for t in np.arange(0, T, dt):
        nest.Simulate(dt)
        print "COMPLETED {0}%\n".format(t / T * 100 + 1)

    endsimulate = datetime.datetime.now()


def get_log(startbuild, endbuild):
    logger.info("Number of neurons  : {}".format(NEURONS))
    logger.info("Number of synapses : {}".format(SYNAPSES))
    logger.info("Building time      : {}".format(endbuild - startbuild))
    logger.info("Simulation time    : {}".format(endsimulate - startsimulate))


def save(GUI):
    global txtResultPath
    if GUI:
        import pylab as pl
        import nest.raster_plot
        import nest.voltage_trace
        logger.debug("Saving IMAGES into {0}".format(SAVE_PATH))
        for key in spike_detectors:
            try:
                nest.raster_plot.from_device(spike_detectors[key], hist=True)
                pl.savefig("spikes_" + str(key) +".png", dpi=dpi_n, format='png')
                pl.close()
            except Exception:
                print("From spikes {0} is NOTHING".format(key))
        for key in multimeters:
            try:
                nest.voltage_trace.from_device(multimeters[key])
                pl.savefig("volt_" + str(key) +".png", dpi=dpi_n, format='png')
                pl.close()
            except Exception:
                print("From MM {0} is NOTHING".format(key))

    txtResultPath = SAVE_PATH + 'txt/'
    logger.debug("Saving TEXT into {0}".format(txtResultPath))
    if not os.path.exists(txtResultPath):
        os.mkdir(txtResultPath)
    for key in spike_detectors:
        save_spikes(spike_detectors[key], name=key)
    with open(txtResultPath + 'timeSimulation.txt', 'w') as f:
        for item in times:
            f.write(item)


def save_spikes(detec, name, hist=False):
    title = "Raster plot from device '%i'" % detec[0]
    ev = nest.GetStatus(detec, "events")[0]
    ts = ev["times"]
    gids = ev["senders"]
    data = defaultdict(list)

    if len(ts):
        with open("{0}@spikes_{1}.txt".format(txtResultPath, name), 'w') as f:
            f.write("Name: {0}, Title: {1}, Hist: {2}\n".format(name, title, "True" if hist else "False"))
            for num in range(0, len(ev["times"])):
                data[round(ts[num], 1)].append(gids[num])
            for key in sorted(data.iterkeys()):
                f.write("{0:>5} : {1:>4} : {2}\n".format(key, len(data[key]), sorted(data[key])))
    else:
        print "Spikes in {0} is NULL".format(name)