from neuron import h, gui
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pyplot
import math
#neuron.load_mechanisms("./mod")
from cfiber import cfiber

def set_recording_vectors(compartment):
    ''' recording voltage
    Parameters
    ----------
    compartment: NEURON section
        compartment for recording 
    Returns
    -------
    v_vec: h.Vector()
        recorded voltage
    t_vec: h.Vector()
        recorded time
    '''
    v_vec = h.Vector()   # Membrane potential vector at compartment
    t_vec = h.Vector()        # Time stamp vector
    v_vec.record(compartment(0.5)._ref_v)
    t_vec.record(h._ref_t)
    return v_vec, t_vec

def balance(cell, vinit=-55):
    ''' voltage balance
    Parameters
    ----------
    cell: NEURON cell
        cell for balance
    vinit: int (mV)
        initialized voltage
    '''
    for sec in cell.all:
        if ((-(sec.ina_nattxs + sec.ina_navv1p8 + sec.ina_Nav1_3 + sec.ina_nakpump) / (vinit - sec.ena)) < 0):
            sec.pumpina_extrapump = -(sec.ina_nattxs + sec.ina_navv1p8 + sec.ina_Nav1_3 + sec.ina_nakpump)
        else:
            sec.gnaleak_leak = -(sec.ina_nattxs + sec.ina_navv1p8 + sec.ina_Nav1_3 + sec.ina_nakpump) / (vinit - sec.ena)

        if ((-(sec.ik_kdr + sec.ik_nakpump + sec.ik_kap + sec.ik_kad) / (vinit - sec.ek)) < 0):
            sec.pumpik_extrapump = -(sec.ik_kdr + sec.ik_nakpump + sec.ik_kap + sec.ik_kad)
        else:
            sec.gkleak_leak = -(sec.ik_kdr + sec.ik_nakpump + sec.ik_kap + sec.ik_kad) / (vinit - sec.ek)

def simulate(cell, tstop=100, vinit=-55):
    ''' simulation control 
    Parameters
    ----------
    cell: NEURON cell
        cell for simulation
    tstop: int (ms)
        simulation time
    vinit: int (mV)
        initialized voltage
    '''
    h.finitialize(vinit)
    balance(cell)
    if h.cvode.active():
        h.cvode.active()
    else:
        h.fcurrent()
    h.frecord_init()
    h.tstop = tstop
    h.v_init = vinit
    h.run()

def show_output(v_vec, t_vec):
    ''' show graphs 
    Parameters
    ----------
    v_vec: h.Vector()
        recorded voltage
    t_vec: h.Vector()
        recorded time
    '''
    dend_plot = pyplot.plot(t_vec, v_vec)
    pyplot.xlabel('time (ms)')
    pyplot.ylabel('mV')

if __name__ == '__main__':
    cell = cfiber(250, 0.25, 100, 0, True)
    for sec in h.allsec():
        h.psection(sec=sec) #show parameters of each section
    branch_vec, t_vec = set_recording_vectors(cell.branch)
    dend_vec, t_vec = set_recording_vectors(cell.stimsec[59])
    simulate(cell)
    show_output(branch_vec, t_vec)
    show_output(dend_vec, t_vec)
    pyplot.show()