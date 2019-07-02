from neuron import h, gui
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pyplot
import math
import random
#neuron.load_mechanisms("./mod")

from cfiber import cfiber
from onefibersimulation import balance

#paralleling NEURON interface
pc = h.ParallelContext()
rank = int(pc.id()) 
nhost = int(pc.nhost())

#parameters
cell_number = 2 # number of neurons 
fibers = []
nclist = []
spike_times_vec = h.Vector()
id_vec = h.Vector()

def addfibers(num = cell_number):
    '''
    Creates neuronal pool and returns gids of pool
    Parameters
    ----------
    num: int
        neurons number in pool
    Returns
    -------
    gids: list
        the list of neurons gids
    '''
    global fibers, rank, nhost, spike_times_vec, id_vec
    gids = []
    for i in range(rank, num, nhost):
        cell = cfiber(random.uniform(200, 350), random.uniform(0.2, 1), random.randint(10, 30), random.randint(0, 10), False)
        fibers.append(cell)
        pc.set_gid2node(i, rank)
        nc = cell.connect2target(None)
        pc.cell(i, nc)
        nclist.append(nc)
        gids.append(i)
        pc.spike_record(i, spike_times_vec, id_vec)
    return gids

def spike_record(pool):
    ''' Records spikes from gids 
    Parameters
    ----------
    pool: list
      list of neurons gids
    Returns
    -------
    v_vec: list of h.Vector()
        recorded voltage
    '''
    v_vec = []
    for i in pool:
        cell = pc.gid2cell(i)
        vec = h.Vector()
        vec.record(cell.branch(0.5)._ref_vext[0])
        v_vec.append(vec)
    return v_vec

def simulate(pool, tstop=30000, vinit=-55):
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
    for i in pool:
        cell = pc.gid2cell(i)
        balance(cell)
    if h.cvode.active():
        h.cvode.active()
    else:
        h.fcurrent()
    h.frecord_init()
    h.tstop = tstop
    h.v_init = vinit
    pc.set_maxstep(0.5)
    h.stdinit()
    pc.psolve(tstop)

def finish():
    ''' proper exit '''
    pc.runworker()
    pc.done()
    h.quit()

def spikeout(pool, name, v_vec):
    ''' Reports simulation results 
    Parameters
    ----------
    pool: list
      list of neurons gids
    name: string
      pool name
    v_vec: list of h.Vector()
        recorded voltage
    '''
    global rank 
    pc.barrier()
    for i in range(nhost):
        if i == rank:
            for j in range(len(pool)):
                path=str('./res/'+ name + '%dr%d'%(j,rank))
                f = open(path, 'w')
                for v in list(v_vec[j]):
                    f.write(str(v)+"\n")
        pc.barrier()

def spiketimeout(file_name):
    ''' Reports simulation results 
    Parameters
    ----------
    pool: list
      list of neurons gids
    name: string
      pool name
    v_vec: list of h.Vector()
        recorded voltage
    '''
    global spike_times_vec, id_vec
    for i in range(int(pc.nhost())):
            pc.barrier() # Sync all processes at this point
            if i == int(pc.id()):
                if i == 0:
                    mode = 'w' # write
                else:
                    mode = 'a' # append
                with open(file_name, mode) as spk_file: # Append
                    for (t, idd) in zip(spike_times_vec, id_vec):
                        spk_file.write('%.3f\t%d\n' %(t, idd)) # timestamp, i
                        print(t)
                        print(idd)
    pc.barrier()
    print(spk_file)


if __name__ == '__main__':
    pool = addfibers()
    vext = spike_record(pool)
    print("- "*10, "\nstart")
    simulate(pool)
    print("- "*10, "\nend")
    spikeout(pool, "vext", vext)
    spiketimeout("out.spk")
    #if (nhost > 1):
    finish()