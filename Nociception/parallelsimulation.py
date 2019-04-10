from neuron import h, gui
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pyplot
import math
import random
#neuron.load_mechanisms("./mod")

from cfiber import cfiber
from onefibersimulation import balance

#paralleling NEURON staff
pc = h.ParallelContext()
rank = int(pc.id()) 
nhost = int(pc.nhost())

#param
cell_number = 3 # number of neurons 
fibers = []

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
    gids = []
    gid = 0
    for i in range(rank, num, nhost):
        cell = cfiber(250, 0.25, 100, random.randint(10, 100), False)
        fibers.append(cell)
        while(pc.gid_exists(gid)!=0):
            gid+=1
        gids.append(gid)
        pc.set_gid2node(gid, rank)
        nc = cell.connect2target(None)
        pc.cell(gid, nc)
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

def simulate(pool, tstop=1000, vinit=-55):
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

if __name__ == '__main__':
    pool = addfibers()
    vext = spike_record(pool)
    print("- "*10, "\nstart")
    simulate(pool)
    print("- "*10, "\nend")
    spikeout(pool, "vext", vext)
    #if (nhost > 1):
    finish()