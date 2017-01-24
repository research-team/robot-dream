import os
import ast
import sys
import nest
import time
import logging
import datetime
import numpy as np
import globals as g
import nest.topology as tp
import matplotlib.pyplot as plt
from collections import defaultdict
from time import clock
from data import *

times = []                  # list for writing time simulation
neighbors = {}              # dict position  : list of neighbors
multimeters = {}            # dict name_part : multimeter
spike_detectors = {}        # dict name_part : spikedetector
spike_generators = {}       # dict name_part : spikegenerator

# Reset all settings
nest.ResetKernel()
# Set new settings
nest.SetKernelStatus({'overwrite_files': True,
                      'local_num_threads': 4,
                      'resolution': 0.1,
                      'print_time': True})
# Set logger format
logging.basicConfig(format='%(name)s.%(levelname)s: %(message)s.', level=logging.DEBUG)
logger = logging.getLogger('function')


def build_model():
    """
    building model
    Cortex
    |-- L2
        |-- 0 column
            |-- Glu:  (10, 12, ...)
            |-- GABA: (20, 21, ...)
        |-- 1 column
            |-- GLu:  (30, 31, ...)
            |-- GABA: (40, 41, ...)
            ...
        L3
        |-- 0 column
        ...
    :return: None
    """
    # Create neurons
    for layer in range(len(Cortex)):
        for column in range(column_number):
            Cortex[layer][column] = dict()
            for neurotransmitter in (Glu, GABA):
                Cortex[layer][column][neurotransmitter] = nest.Create('iaf_psc_exp',
                                                                      cortex_params[layer][neurotransmitter],
                                                                      params=cortex_params[layer][k_param])
                g.neuron_number += cortex_params[layer][neurotransmitter]
    # Search neighbors by position
    logger.debug("* * * Creating MAP")
    print np.arange(column_number).reshape(Y, X)
    for y in range(Y):
        for x in range(X):
            right = left = top = bottom = False
            position = y*X + x
            neighbors[position] = list()
            proxy = neighbors[position]
            if position + 1 < X*(y + 1):
                proxy.append(position+1)
                right = True
            if position - 1 >= y*X:
                proxy.append(position - 1)
                left = True
            if position + X < column_number:
                proxy.append(position + X)
                bottom = True
            if position - X >= 0:
                proxy.append(position - X)
                top = True
            if top:
                if right:
                    proxy.append(position - X + 1)
                if left:
                    proxy.append(position - X - 1)
            if bottom:
                if right:
                    proxy.append(position + X + 1)
                if left:
                    proxy.append(position + X - 1)
            del proxy
    print neighbors


def big_wave(start=0.0, stop=T, rate_HZ=10, percent=30, weight=Glu):
    """

    :param start:
    :param stop:
    :param rate_HZ:
    :param percent:
    :param weight:
    :return:
    """
    rate_ms = 1. / rate_HZ * 1000
    coef_part = float(percent) / 100
    syn_spec = {'weight': weight + 700.,
                'delay': 0.1}
    # Init spike times with step "rate_ms"
    spikes = list()
    for item in np.arange(start, stop, rate_ms)[1:]:
        spikes.append(item)
        spikes.append(item + 0.1)
        spikes.append(item + 0.4)
        spikes.append(item + 0.7)
        spikes.append(item + 1.0)
    print spikes
    # Create generator
    wave_generator = nest.Create('spike_generator', 1)
    nest.SetStatus(wave_generator, {'spike_times': spikes, 'spike_weights': [1. for i in spikes]})
    # Connect generator
    for layer in range(len(Cortex)):
        for column in range(column_number):
            part = Cortex[layer][column][GABA]
            conn_spec = {'rule': 'fixed_outdegree',
                         'outdegree': int(len(part) * coef_part)}
            nest.Connect(wave_generator, part, conn_spec=conn_spec, syn_spec=syn_spec)
            del part


def connect(pre, post, neurotransmitter=GABA, weight_coef=1, conn_prob=1.):
    """

    :param pre:
    :param post:
    :param neurotransmitter:
    :param weight_coef:
    :param conn_prob:
    :return:
    """
    if type(pre) is dict:
        if k_IDs in pre:
            pre = tuple(pre[k_IDs])
    if type(post) is dict:
        if k_IDs in post:
            post = tuple(post[k_IDs])

    # Set new weight value (weight_coef * basic weight)
    neurotransmitters[neurotransmitter][model]['weight'] = weight_coef * neurotransmitters[neurotransmitter][basic_weight]
    # Correlate number of synapses
    current_synapses = int(len(post)*conn_prob)
    if current_synapses > max_synapse:
        current_synapses = max_synapse
    elif current_synapses < min_synapse:
        current_synapses = min_synapse
    # Update number of synapses
    g.synapse_number += current_synapses
    # Create dictionary of connection rules
    conn_dict = {'rule': 'fixed_outdegree',
                 'outdegree': current_synapses,
                 'multapses': True,  # multiple connections between a pair of nodes
                 'autapses': False}  # self-connections
    # Connect neurons
    nest.Connect(pre, post, conn_spec=conn_dict, syn_spec=neurotransmitters[neurotransmitter][model])
    # Show data of a new connection
    print '|-- Connect ({0}...{1}) to ({2}...{3}) W= {4:<6} P_conn= {5:<4}% ({6}/{7})'.format(
        pre[:1][0], pre[-1:][0],
        post[:1][0], post[-1:][0],
        neurotransmitters[neurotransmitter][model]['weight'],
        conn_prob * 100,
        current_synapses, len(post))


def connect_generator(part, startTime=1, stopTime=T, rate=250, coef_part=1.0, weight=w_Glu*2, delay=pg_delay):
    """

    :param part:
    :param startTime:
    :param stopTime:
    :param rate:
    :param coef_part:
    :param weight:
    :param delay:
    :return:
    """
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


def specific_generator(part, coef_part=1.0, weight=740. + 400, delay=pg_delay):
    """

    :param part:
    :param coef_part:
    :param weight:
    :param delay:
    :return:
    """
    # Create dictionary of connection and synapse specification
    conn_spec = {'rule': 'fixed_outdegree',
                 'outdegree': int(len(part) * coef_part)}

    syn_spec = {'weight': weight,
                'delay': delay}

    intervals = raw.split(" ")
    spikes = [0.0]
    for i in range(len(intervals)):
        element = float("%.1f" % (spikes[i] + float(intervals[i]) / 1000))
        if element >= T:
            break
        spikes.append(element)
    del spikes[0]

    print spikes

    generator = nest.Create('spike_generator', 1)
    nest.SetStatus(generator, {'spike_times': spikes, 'spike_weights': [1. for i in spikes]})

    # Connect generator and part IDs with connection specification and synapse specification
    nest.Connect(generator, part, conn_spec=conn_spec, syn_spec=syn_spec)


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


def build_column_key(column, neurotransmitter, dt=None, heatmap=None):
    return "column_{0}_{1}_{2}_{3}".format(column, get_neurotransmitter_name(neurotransmitter), dt, heatmap)


def build_layer_key(index, neurotransmitter, dt=None, heatmap=None):
    return "layer_{0}_{1}_{2}_{3}".format(index, get_neurotransmitter_name(neurotransmitter), dt, heatmap)


def set_flag_to_column(column, neurotransmitter, heatmap=False, dt=1, multimeter=False):
    for neurotransmitter in (Glu, GABA) if neurotransmitter == both else (neurotransmitter,):
        key = build_column_key(column, neurotransmitter, dt, heatmap)
        spike_detectors[key] = dict()
        if multimeter:
            multimeters[key] = dict()
        for layer in range(len(Cortex)):
            neuron_number = len(Cortex[layer][column][neurotransmitter])
            if multimeter:
                multimeters[key][layer] = nest.Create('multimeter', params=multimeter_param)
                nest.Connect(multimeters[key][layer], Cortex[layer][column][neurotransmitter][::neuron_number / N_volt])
            spike_detectors[key][layer] = nest.Create('spike_detector', params=detector_param)
            nest.Connect(Cortex[layer][column][neurotransmitter][:N_detect], spike_detectors[key][layer])


def set_flag_to_layer(layer, neurotransmitter=Glu, heatmap=True, dt=1, multimeter=False):
    for neurotransmitter in (Glu, GABA) if neurotransmitter == both else (neurotransmitter,):
        key = build_layer_key(layer, neurotransmitter, dt, heatmap)
        spike_detectors[key] = dict()
        if multimeter:
            multimeters[key] = dict()
        for column in range(column_number):
            neuron_number = len(Cortex[layer][column][neurotransmitter])
            if multimeter:
                multimeters[key][column] = nest.Create('multimeter', params=multimeter_param)
                nest.Connect(multimeters[key][column], Cortex[layer][column][neurotransmitter][::neuron_number / N_volt])
            spike_detectors[key][column] = nest.Create('spike_detector', params=detector_param)
            nest.Connect(Cortex[layer][column][neurotransmitter][:N_detect], spike_detectors[key][column])


def get_layer_name(index):
    return layers_name[index]


def get_neurotransmitter_name(neurotransmitter):
    return 'Glu' if neurotransmitter == 0 else 'GABA'


def create_subdir(subfolder, parent):
    """

    :param subfolder:
    :param parent:
    :return:
    """
    directory = "{0}/{1}".format(parent, subfolder)
    if not os.path.exists(directory):
        os.makedirs(directory)
    return directory


def save_layer_data(key, value, isMultimeter=False):
    """

    :param key:
    :param value:
    :param isMultimeter:
    :return:
    """
    # Get parameters from string
    params = str(key).split("_")
    area = params[0]
    layer_name = get_layer_name(int(params[1]))
    neurotransmitter = params[2]

    parent_dir = "{0}_{1}[{2}]".format(area, layer_name, neurotransmitter)
    if not os.path.exists(parent_dir):
        os.mkdir(parent_dir)

    if isMultimeter:
        addres = create_subdir('voltage', parent_dir)
        for column, device in value.iteritems():
            nest.voltage_trace.from_device(device, title="Membrane potential in {0} column {1}".format(layer_name, column))
            plt.savefig("{0}/{1}.{2}".format(addres, column, image_format), dpi=dpi_n, format=image_format)
            plt.close()
    else:
        dt = int(params[3])
        heatmap = bool(params[4])
        addres = create_subdir('spikes', parent_dir)
        for column, device in value.iteritems():
            try:
                nest.raster_plot.from_device(device, hist=True, title="Spikes {0} column {1}".format(layer_name, column))
                plt.savefig("{0}/{1}.{2}".format(addres, column, image_format), dpi=dpi_n, format=image_format)
                plt.close()
            except nest.NESTError:
                print "From column {0} {1}[{2}] activity was not found".format(column, layer_name, neurotransmitter)
        if heatmap:
            addres = create_subdir('heatmap', parent_dir)
            heatmap_builder(addres, value, dt, isColumn=False)


def save_column_data(key, value, isMultimeter=False):
    """

    :param key:
    :param value:
    :param isMultimeter:
    :return:
    """
    # Get parameters from string
    params = str(key).split("_")
    area = params[0]
    column = int(params[1])
    neurotransmitter = params[2]

    parent_dir = "{0}_{1}[{2}]".format(area, column, neurotransmitter)
    if not os.path.exists(parent_dir):
        os.mkdir(parent_dir)

    if isMultimeter:
        addres = create_subdir('voltage', parent_dir)
        for layer, device in value.iteritems():
            nest.voltage_trace.from_device(device, title="Membrane potential in {0} column {1}".format(get_layer_name(layer), column))
            plt.savefig("{0}/{1}.{2}".format(addres, get_layer_name(layer), image_format), dpi=dpi_n, format=image_format)
            plt.close()
    else:
        dt = int(params[3])
        heatmap = bool(params[4])
        addres = create_subdir('spikes', parent_dir)
        for layer, device in value.iteritems():
            try:
                nest.raster_plot.from_device(device, hist=True, title="Spikes {0} column {1}".format(get_layer_name(layer), column))
                plt.savefig("{0}/{1}.{2}".format(addres, get_layer_name(layer), image_format), dpi=dpi_n, format=image_format)
                plt.close()
            except nest.NESTError:
                print "From column {0} {1}[{2}] activity was not found".format(column, get_layer_name(layer), neurotransmitter)
        if heatmap:
            addres = create_subdir('heatmap', parent_dir)
            heatmap_builder(addres, value, dt, isColumn=True)


def save_data(key, value, isMultimeter=False):
    """

    :param key:
    :param value:
    :param isMultimeter:
    :return:
    """
    if not os.path.exists(key):
        os.mkdir(key)

    if isMultimeter:
        nest.voltage_trace.from_device(value)
        plt.savefig("volt_{0}.{1}".format(key, image_format), dpi=dpi_n, format=image_format)
        plt.close()
    else:
        try:
            nest.raster_plot.from_device(value, hist=True)
            plt.savefig("spikes_{0}.{1}".format(key, image_format), dpi=dpi_n, format=image_format)
            plt.close()
        except nest.NESTError:
            print("From {0} no actiity".format(key))


def heatmap_builder(folder, value, dt, isColumn=False):
    """

    :param folder:
    :param value:
    :param dt:
    :param isColumn:
    :return:
    """

    # Import additional lib for working with heatmap
    import seaborn as sns
    sns.set()

    dt *= 10        # correlate dt
    heatmap = []    # main list of data
    max_value = 0   # max number of spikes

    # Collect data from spikedetectors
    for key, detector in value.iteritems():
        # Additional variable
        collapsed = []
        # Initialize list to store number of spikes at each time
        size = int(T) * 10
        spikes_list = [0 for i in range(size)]

        # Set number of spikes (times: list with times when was a spike)
        for spike_time in nest.GetStatus(detector, 'events')[0]['times']:
            spikes_list[int(spike_time * 10)] += 1

        # Collapse time intervals to the 'dt'
        for i in range(0, size, dt):
            collapsed.append(sum(spikes_list[i:i + dt]))
        # Append collapsed list to the main list of data
        heatmap.append(collapsed)

        # Find max number of spikes (for the colorbar)
        max_value = max(collapsed) if max(collapsed) > max_value else max_value
        # Free memory
        del collapsed

    # For each time interval create heatmap
    # ToDo test size/dt variants
    for step in xrange(size / dt):
        data = []   # tmp list of data
        # Build data for heatmap prejection
        if isColumn:
            # Build data for heatmap prejection
            for line in range(len(Cortex)):
                data.append([heatmap[line][step]])
        else:
            start = 0   # tmp index
            for line in range(Y):
                temp = []   # tmp list
                # Get value for current step for each elements in line
                for element in range(start, X + start):
                    temp.append(heatmap[element][step])
                data.append(temp)
                # Move down (in index)
                start += X
                # Free memory
                del temp
        # Set titles in figure
        plt.title("Step {0}/{1}".format(step + 1, size / dt))
        if not isColumn:
            plt.xlabel("X")
            plt.ylabel("Y")

        # Create figure
        af = sns.heatmap(data, annot=True, fmt="d", cmap='hot', vmin=0, vmax=max_value)
        if isColumn:
            af.set(yticklabels=["L6", "L5B", "L5A", "L4", "L3", "L2"])
            #af.set(xticklabels=['Column ' + str(index)])

        colorbar = af.collections[0].colorbar
        # Set 11 values (with zero) to colorbar
        full_bar_ticks = range(max_value + 1)
        bar_ticks = (max_value + 1) / 10
        colorbar.set_ticks(full_bar_ticks[::2] if bar_ticks <= 1 else full_bar_ticks[::bar_ticks])
        # Save figure
        plt.savefig("{0}/{1}.png".format(folder, step+1), dpi=dpi_n, format='png')
        plt.close()

        # Free memory
        del data, full_bar_ticks


def simulate():
    logger.debug('* * * Simulating')
    g.startsimulate = datetime.datetime.now()
    nest.Simulate(T)
    g.endsimulate = datetime.datetime.now()


def log():
    logger.info("Number of neurons  : {:,}".format(g.neuron_number).replace(",", " "))
    logger.info("Number of synapses : {:,}".format(g.synapse_number).replace(",", " "))
    logger.info("Building time      : {}".format(g.endbuild - g.startbuild))
    logger.info("Simulation time    : {}".format(g.endsimulate - g.startsimulate))


def save():
    """

    :return: None
    """
    # Create current folder
    datapath = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
    if not os.path.exists(datapath):
        os.mkdir(datapath)
    os.chdir(datapath)

    if gui_flag:
        import nest.raster_plot
        import nest.voltage_trace
        for key, value in spike_detectors.items():
            if 'layer' in key:
                save_layer_data(key, value)
            elif 'column' in key:
                save_column_data(key, value)
            else:
                save_data(key, value)
            del spike_detectors[key]
        for key, value in multimeters.items():
            if 'layer' in key:
                save_layer_data(key, value, isMultimeter=True)
            elif 'column' in key:
                save_column_data(key, value, isMultimeter=True)
            else:
                save_data(key, value, isMultimeter=True)
            del multimeters[key]
    else:
        if not os.path.exists("text"):
            os.mkdir("text")
        os.chdir("text")

        logger.debug("Saving TEXT into {0}".format(txtResultPath))
        if not os.path.exists(txtResultPath):
            os.mkdir(txtResultPath)
        for key in spike_detectors:
            save_spikes(spike_detectors[key], name=key)
        with open("{0}/{1}".format(txtResultPath, txtTimeSimulation), 'w') as f:
            for item in times:
                f.write(item)


def save_spikes(detec, name, hist=False):
    """

    :param detec:
    :param name:
    :param hist:
    :return:
    """
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