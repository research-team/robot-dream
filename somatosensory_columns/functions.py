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
import ast
import time

neighbors = {}
multimeters = {}            # dict name_part : spikedetector
spike_generators = {}       # dict name_part : spikegenerator
spike_detectors = {}        # dict name_part : spikedetector
txtResultPath = ""          # path for txt result
MaxSynapses = 500            # max synapses
MinSynapses = 10
startsimulate = 0           # begin of simulation
endsimulate = 0             # end of simulation
SAVE_PATH = ""              # path to save results
SYNAPSES = 0                # number of synapses
NEURONS = 0                 # number of neurons
times = []                  # list for writing time simulation


FORMAT = '%(name)s.%(levelname)s: %(message)s.'
logging.basicConfig(format=FORMAT, level=logging.DEBUG)
logger = logging.getLogger('function')


def connect(pre, post, syn_type=GABA, weight_coef=1, conn_prob=1.):
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
    synapses[syn_type][model]['weight'] = weight_coef * synapses[syn_type][basic_weight]

    current_synapses = int(len(post)*conn_prob)
    if current_synapses > MaxSynapses:
        current_synapses = MaxSynapses
    elif current_synapses < MinSynapses:
        current_synapses = MinSynapses

    # Create dictionary of connection rules
    conn_dict = {'rule': 'fixed_outdegree',
                 'outdegree': current_synapses,
                 'multapses': True,  # multiple connections between a pair of nodes
                 'autapses': False}  # self-connections
    # Connect PRE IDs neurons with POST IDs neurons, add Connection and Synapse specification
    nest.Connect(pre, post, conn_spec=conn_dict, syn_spec=synapses[syn_type][model])

    # Show data of new connection
    print 'Connect {0}...{1} to {2}...{3}; W={4}; P_conn={5}%'.format(pre[:1], pre[-1:],
                                                                      post[:1], post[-1:],
                                                                      synapses[syn_type][model]['weight'],
                                                                      conn_prob * 100)


def getNeighbors(column):
    return neighbors[column]


def generate_dict(layer):
    if layer == 0:
        return dict(dict(E_L=   np.random.normal(L2_EL_mu,   L2_EL_sigma),
                         V_th=  np.random.normal(L2_Vth_mu,  L2_Vth_sigma),
                         C_m=   np.random.normal(L2_Cm_mu,   L2_Cm_sigma),
                         t_ref= np.random.normal(L2_tref_mu, L2_tref_sigma), **global_neuron_parameters))
    elif layer == 1:
        return dict(dict(E_L=   np.random.normal(L3_EL_mu,   L3_EL_sigma),
                         V_th=  np.random.normal(L3_Vth_mu,  L3_Vth_sigma),
                         C_m=   np.random.normal(L3_Cm_mu,   L3_Cm_sigma),
                         t_ref= np.random.normal(L3_tref_mu, L3_tref_sigma), **global_neuron_parameters))
    elif layer == 2:
        return dict(dict(E_L=   np.random.normal(L4_EL_mu,   L4_EL_sigma),
                         V_th=  np.random.normal(L4_Vth_mu,  L4_Vth_sigma),
                         C_m=   np.random.normal(L4_Cm_mu,   L4_Cm_sigma),
                         t_ref= np.random.normal(L4_tref_mu, L4_tref_sigma), **global_neuron_parameters))
    elif layer == 3:
        return dict(dict(E_L=   np.random.normal(L5A_EL_mu,   L5A_EL_sigma),
                         V_th=  np.random.normal(L5A_Vth_mu,  L5A_Vth_sigma),
                         C_m=   np.random.normal(L5A_Cm_mu,   L5A_Cm_sigma),
                         t_ref= np.random.normal(L5A_tref_mu, L5A_tref_sigma), **global_neuron_parameters))
    elif layer == 4:
        return dict(dict(E_L=   np.random.normal(L5B_EL_mu,   L5B_EL_sigma),
                         V_th=  np.random.normal(L5B_Vth_mu,  L5B_Vth_sigma),
                         C_m=   np.random.normal(L5B_Cm_mu,   L5B_Cm_sigma),
                         t_ref= np.random.normal(L5B_tref_mu, L5B_tref_sigma), **global_neuron_parameters))
    else:
        return dict(dict(E_L=   np.random.normal(L6_EL_mu,   L6_EL_sigma),
                         V_th=  np.random.normal(L6_Vth_mu,  L6_Vth_sigma),
                         C_m=   np.random.normal(L6_Cm_mu,   L6_Cm_sigma),
                         t_ref= np.random.normal(L6_tref_mu, L6_tref_sigma), **global_neuron_parameters))



def build_model(column_number):
    global NEURONS, neighbors
    layer_num = 0
    for layer in Cortex:
        print layer
        for mediator in layer[:2]:
            for column in range(column_number):
                mediator[column] = nest.Create('iaf_psc_exp', mediator[k_NN], params=generate_dict(layer_num))
                NEURONS += mediator[k_NN]
        layer_num+=1

    Thalamus[Glu][k_IDs] = nest.Create("iaf_psc_exp", Thalamus[Glu][k_NN])
    Striatum[Glu][k_IDs] = nest.Create("iaf_psc_exp", Striatum[Glu][k_NN])
    POm[Glu][k_IDs] = nest.Create("iaf_psc_exp", POm[Glu][k_NN])

    print NEURONS

    logger.debug("* * * Creating MAP")
    print np.arange(GlobalColumns).reshape(Y, X)

    for y in range(Y):
        for x in range(X):
            right = left = top = bottom = False
            current = y * X + x
            neighbors[current] = list()
            proxy = neighbors[current]
            if current + 1 < X * (y + 1):
                proxy.append(current+1)
                right = True
            if current - 1 >= y * X:
                proxy.append(current-1)
                left = True
            if current + X < GlobalColumns:
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
            del proxy
    print neighbors


def connect_generator(part, startTime=1, stopTime=T, rate=250, coef_part=1.0, weight=w_Glu*2, delay=pg_delay):
    name = part[k_name]
    # Add to spikeGenerators dict a new generator
    spike_generators[name] = nest.Create('poisson_generator', 1, {'rate' : float(rate),
                                                                  'start': float(startTime),
                                                                  'stop' : float(stopTime)})
    # Create dictionary of connection and synapse specification
    conn_spec = {'rule': 'fixed_outdegree',
                 'outdegree': int(part[k_NN] * coef_part)}

    syn_spec = {'weight': weight,
                'delay': delay}

    # Connect generator and part IDs with connection specification and synapse specification
    nest.Connect(spike_generators[name], part[k_IDs], conn_spec=conn_spec, syn_spec=syn_spec)
    # Show data of new generator
    logger.debug("Generator => {0}. Element #{1}".format(name, spike_generators[name][0]))


def specific_generator(part, coef_part=1.0, weight=w_Glu, delay=pg_delay):
    # Create dictionary of connection and synapse specification
    conn_spec = {'rule': 'fixed_outdegree',
                 'outdegree': int(len(part) * coef_part)}

    syn_spec = {'weight': weight,
                'delay': delay}

    raw = "1300 1600 1600 3250 2500 2900 3100 2700 3350 1400 1550 1600 1500 1550 1650 1650 1700 1450 2900 2850 3250 3000 2700 2750 1700 1700 1650 1700 1550 1700 1650 1700 1500 1700 1650 1650 2750 3100 3000 2950 2950 3000 3100 3100 3250 3100 1200 1450 1450 1400 1550 1650 1700 1600 1700 1650 1450 1650 1600 1550 1400 1700 3100 3200 3400 3100 3100 3000 2950 1400 1350 1250 1250 1250 1250 1000 1150 1300 1300 1250 1250 1250 1300 1250 1250 1000 3050 2950 3100 3150 3000 3350 3100 3000 2950 1100 1500 1550 1500 1500 1350 1350 1400 1400 1350 1400 1250 1300 1350 1200 1400 1250 1400 1400 1300 1400 1400 1400 1400 1200 1300 1300 1200 1400 1100 1400 1400 1200 1300 1300 1200 1400 1400 1400 1400 1400 1400 1350 1400 1250 1300 1200 1400 1250 1200 1300 1400 1400 1400 1350 1350 1350 1150 1350 1400 1250 1150 1200 1400 1350 1400 1300 1400 2750 3100 2950 2700 2400 2050 2300 2300 2300 2150 2300 2300 2400 2050 2200 2300 2300 2300 2300 2400 2200 2150 2300 2250 2000 2200 2250 1950 2100 2100 2200 2200 2100 2300 2150 2200 1950 2100 1800 2750 2600 2850 2650 2750 2750 2600 2750 2600 2750 2850 2850 2500 2850 2800 2300 2600 2750 2450 2450 2750 2450 2750 2750 2850 2600 2600 2450 2750 1450 3150 3200 3450 2800 3050 3050 3400 3250 3100"
    intervals = raw.split(" ")
    spikes = [0.0]
    for i in range(len(intervals)):
        spikes.append(float("%.1f" % (spikes[i] + float(intervals[i]) / 1000)))

    # =================
    generator1 = nest.Create('spike_generator', 1)
    nest.SetStatus(generator1, {'spike_times': spikes[1:], 'spike_weights': [500. for i in spikes[1:]]})

    # Connect generator and part IDs with connection specification and synapse specification
    nest.Connect(generator1, part, conn_spec=conn_spec, syn_spec=syn_spec)


def connect_detector(part):
    name = part[k_name]
    # Add to spikeDetectors a new detector
    spike_detectors[name] = nest.Create('spike_detector', params=detector_param)
    # ToDo if N_detect > NN_number then will be taken max of this list -- NN_number
    nest.Connect(part[k_IDs][:N_detect], spike_detectors[name])
    # Show data of new detector
    logger.debug("Detector => {0}. Tracing neurons".format(name))


def connect_multimeter(part):
    name = part[k_name]
    multimeters[name] = nest.Create('multimeter', params=multimeter_param)  # ToDo add count of multimeters
    nest.Connect(multimeters[name], part[k_IDs][:N_volt])
    logger.debug("Multimeter => {0}. On {1}".format(name, part[k_IDs][:N_volt]))


def getAllParts():
    return all_parts


def get_column_name(column):
    return "col_"+str(column)

def get_layer_key(layer):
    return "layer_"+str(layer)

def setFlagToColumn(column):
    name = get_column_name(column)
    spike_detectors[name] = {'L2':  nest.Create('spike_detector', params=detector_param),
                             'L3':  nest.Create('spike_detector', params=detector_param),
                             'L4':  nest.Create('spike_detector', params=detector_param),
                             'L5A': nest.Create('spike_detector', params=detector_param),
                             'L5B': nest.Create('spike_detector', params=detector_param),
                             'L6':  nest.Create('spike_detector', params=detector_param)}

    multimeters[name] = {'L2':  nest.Create('multimeter', params=multimeter_param),
                         'L3':  nest.Create('multimeter', params=multimeter_param),
                         'L4':  nest.Create('multimeter', params=multimeter_param),
                         'L5A': nest.Create('multimeter', params=multimeter_param),
                         'L5B': nest.Create('multimeter', params=multimeter_param),
                         'L6':  nest.Create('multimeter', params=multimeter_param)}

    #ToDo if N_detect > NN_number then will be taken max of this list -- NN_number
    nest.Connect(Cortex[L2][Glu][column][:N_detect],  spike_detectors[name]['L2'])
    nest.Connect(Cortex[L3][Glu][column][:N_detect],  spike_detectors[name]['L3'])
    nest.Connect(Cortex[L4][Glu][column][:N_detect],  spike_detectors[name]['L4'])
    nest.Connect(Cortex[L5A][Glu][column][:N_detect], spike_detectors[name]['L5A'])
    nest.Connect(Cortex[L5B][Glu][column][:N_detect], spike_detectors[name]['L5B'])
    nest.Connect(Cortex[L6][Glu][column][:N_detect],  spike_detectors[name]['L6'])

    nest.Connect(multimeters[name]['L2'],  Cortex[L2][Glu][column][:N_volt])
    nest.Connect(multimeters[name]['L3'],  Cortex[L3][Glu][column][:N_volt])
    nest.Connect(multimeters[name]['L4'],  Cortex[L4][Glu][column][:N_volt])
    nest.Connect(multimeters[name]['L5A'], Cortex[L5A][Glu][column][:N_volt])
    nest.Connect(multimeters[name]['L5B'], Cortex[L5B][Glu][column][:N_volt])
    nest.Connect(multimeters[name]['L6'],  Cortex[L6][Glu][column][:N_volt])


def setFlagToLayer(layer):
    layer_key = get_layer_key(layer)
    spike_detectors[layer_key] = dict()

    #FixMe: Here only for Glu
    for column in range(GlobalColumns):
        spike_detectors[layer_key][column] = nest.Create('spike_detector', params=detector_param)
        nest.Connect(Cortex[layer][Glu][column][:N_detect], spike_detectors[layer_key][column])

def getFullDataOfColumn(column_N):
    column_name = get_column_name(column_N)
    if status_gui:
        import pylab as pl
        import nest.raster_plot
        import nest.voltage_trace

        if not os.path.exists(column_name):
            os.mkdir(column_name)

        for layer_name, detector in spike_detectors[column_name].iteritems():
            try:
                nest.raster_plot.from_device(detector, hist=True, title="Spikes in column {0} {1}".format(column_N, layer_name))
                pl.savefig("{0}/spikes_{1}_{0}.png".format(column_name, layer_name), dpi=dpi_n, format='png')
                pl.close()
            except Exception:
                print("From layer {} activity was not found".format(layer_name))
        for layer_name, multimeter  in multimeters[column_name].iteritems():
            nest.voltage_trace.from_device(multimeter, title="Membrane potential in column {0} {1}".format(column_N, layer_name))
            pl.savefig("{0}/volt_{1}_{0}.png".format(column_name, layer_name), dpi=dpi_n, format='png')
            pl.close()
    del spike_detectors[column_name], multimeters[column_name]


def getMapOfLayer(layer, dt):
    import seaborn as sns
    sns.set()

    dt *= 10
    heatmap = []
    layer_key = get_layer_key(layer)
    max_value = 0
    for column, detector in spike_detectors[layer_key].iteritems():
        print column, detector
        size = int(T) * 10
        layer_spikes_in_time = [0 for i in range(size)]

        for time in nest.GetStatus(detector, 'events')[0]['times']:
            layer_spikes_in_time[int(time * 10)] += 1

        collapsed = []

        for i in range(0, size, dt):
            collapsed.append(sum(layer_spikes_in_time[i:i + dt]))
        max_value = max(collapsed) if max(collapsed) > max_value else max_value
        heatmap.append(collapsed)

    for step in range(size/ dt):
        data = []
        start = 0
        for line in range(Y):
            temp = []
            for element in range(start, X + start):
                temp.append(heatmap[element][step])
            start += X
            data.append(temp)

        print data
        plt.title("Step {0}/{1}".format(step + 1, size / dt))
        plt.xlabel("X")
        plt.ylabel("Y")

        af = sns.heatmap(data, annot=True, fmt="d", cmap='hot', vmin=0, vmax=max_value)
        colorbar = af.collections[0].colorbar
        colorbar.set_ticks(range(max_value + 1))
        plt.show()
        del data
    del spike_detectors[layer_key]

def simulate():
    global startsimulate, endsimulate, SAVE_PATH
    logger.debug('* * * Simulating')
    startsimulate = datetime.datetime.now()

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


'''
#############################################
#############################################
from matplotlib.widgets import Button

fig, ax = plt.subplots()

data = []
start = 0
for line in range(Y):
    temp = []
    for element in range(start, X + start):
        temp.append(heatmap[element][0])
    start += X
    data.append(temp)

af = sns.heatmap(data, annot=True, fmt="d", cmap='hot', vmin=0, vmax=max_value)
colorbar = af.collections[0].colorbar
colorbar.set_ticks(range(max_value + 1))

plt.subplots_adjust(bottom=0.2)


class Index(object):
    step_sm = 0

    def next(self, event):
        self.step_sm += 1
        if self.step_sm < len(collapsed):
            data_n = []
            start_n = 0
            for line_n in range(Y):
                temp_n = []
                for element_n in range(start_n, X + start_n):
                    temp_n.append(heatmap[element_n][self.step_sm])
                start_n += X
                data_n.append(temp_n)
            print  data_n
            af.set(data=data_n)

            plt.draw()
        else:
            pass

    def prev(self, event):
        self.step_sm -= 1

        data_n = []
        start_n = 0
        for line_n in range(Y):
            temp_n = []
            for element_n in range(start_n, X + start_n):
                temp_n.append(heatmap[element_n][self.step_sm])
            start_n += X
            data_n.append(temp_n)

        af = sns.heatmap(data_n, annot=True, fmt="d", cmap='hot', vmin=0, vmax=max_value)
        plt.draw()


callback = Index()
axprev = plt.axes([0.1, 0.05, 0.1, 0.075])
axnext = plt.axes([0.81, 0.05, 0.1, 0.075])
bnext = Button(axnext, 'Next')
bnext.on_clicked(callback.next)
bprev = Button(axprev, 'Prev')
bprev.on_clicked(callback.prev)
plt.show()



#####################################
#####################################
'''
