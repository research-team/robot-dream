from neuron import h, gui
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pyplot
import math
#neuron.load_mechanisms("./mod")

class cfiber(object):
    def __init__(self):
        self.coordinates = dict()
        self.diffs = []
        self.recs = []
        self.L = 250
        self.diam = 0.25
        self.create_sections()
        self.build_topology()
        self.build_subsets()
        self.define_geometry()
        self.position()
        self.define_biophysics()
    def create_sections(self):
        self.branch = h.Section(name='branch', cell=self)
        self.stimsec = [h.Section(name='stimsec[%d]' % i) for i in range(120)]
    def build_topology(self):
        self.stimsec[0].connect(self.branch(0), 1)
        for i in range(1, len(self.stimsec)):
            self.stimsec[i].connect(self.stimsec[i-1])
    def define_geometry(self):
        for sec in self.stimsec:
            sec.L = self.L# microns
            sec.diam = self.diam # microns
        self.branch.L = self.L
        self.branch.diam = self.diam
        self.branch.nseg = 1
        h.define_shape() # Translate into 3D points.
    def position(self):
        i = 0
        for sec in self.all:
          h.pt3dclear()
          h.pt3dadd(self.L*i, 0, 0, self.diam)
          h.pt3dadd(self.L*(i+1), 0, 0, self.diam)
          xyz = dict(x=self.L*(i+1), y=0, z=0)
          self.coordinates.update({sec: xyz})
          i+=1
        print(self.coordinates)
    def define_biophysics(self):
        for sec in self.all: # 'all' defined in build_subsets
            sec.Ra = 35    # Axial resistance in Ohm * cm
            sec.cm = 1      # Membrane capacitance in micro Farads / cm^2
            sec.insert('navv1p8')
            sec.insert('extrapump')
            sec.insert('koi')
            sec.insert('naoi')
            sec.insert('kna')
            sec.insert('nakpump')
            sec.insert('nattxs')
            sec.insert('kdr')
            sec.insert('kad')
            sec.insert('kap')
            sec.insert('leak')
            sec.insert('Nav1_3')
            sec.gbar_navv1p8 = 0.2
            sec.gbar_kdr = 0#0.01
            sec.gbar_kad = 0.1
            sec.gbar_kap = 0.1
            sec.gbar_nattxs = 0.1
            sec.gbar_Nav1_3 = 0.2
            sec.smalla_nakpump = -0.0047891
            sec.theta_naoi = 0.029
            sec.theta_koi = 0.029
            sec.celsiusT_nattxs = 37
            sec.celsiusT_navv1p8 = 37
            sec.celsiusT_nakpump = 37
        for sec in self.stimsec:
            self.add_P2X3receptors(sec, 15000, 10, 12)
            self.add_5HTreceptors(sec, 15000, 10, 3)
    def add_P2X3receptors(self, compartment, x, time, g):
        diff = h.AtP_4(compartment(0.5))
        rec = h.p2x3(compartment(0.5))
        rec.gmax = g
        rec.Ev = 5
        diff.h = math.sqrt((x-self.coordinates.get(compartment).get('x'))**2 + (0-self.coordinates.get(compartment).get('y'))**2 + (0.001-self.coordinates.get(compartment).get('z'))**2)
        diff.tx1 = time
        diff.Deff = 0.8 
        diff.c0cleft = 10
        h.setpointer(diff._ref_atp, 'patp', rec)
        self.diffs.append(diff)
        self.recs.append(rec)  
    def add_5HTreceptors(self, compartment, x, time, g):
        diff = h.AtP_4(compartment(0.5))
        rec = h.r5ht3a(compartment(0.5))
        rec.gmax = g
        diff.h = math.sqrt((x-self.coordinates.get(compartment).get('x'))**2 + (0-self.coordinates.get(compartment).get('y'))**2 + (0.001-self.coordinates.get(compartment).get('z'))**2)
        diff.tx1 = time
        diff.Deff = 0.8 
        diff.c0cleft = 2
        h.setpointer(diff._ref_atp, 'serotonin', rec)
        self.diffs.append(diff)
        self.recs.append(rec)      
    def build_subsets(self):
        self.all = h.SectionList()
        for sec in h.allsec():
          self.all.append(sec=sec)  

def set_recording_vectors(cell):
    branch_v_vec = h.Vector()   # Membrane potential vector at soma
    stimsec_v_vec = h.Vector()   # Membrane potential vector at dendrite
    t_vec = h.Vector()        # Time stamp vector
    branch_v_vec.record(cell.branch(0.5)._ref_v)
    stimsec_v_vec.record(cell.stimsec[59](0.5)._ref_v)
    t_vec.record(h._ref_t)
    return branch_v_vec, stimsec_v_vec, t_vec

def balance(cell, vinit=-55):
    for sec in cell.all:
        if ((-(sec.ina_nattxs + sec.ina_navv1p8 + sec.ina_Nav1_3 + sec.ina_nakpump) / (vinit - sec.ena)) < 0):
            sec.pumpina_extrapump = -(sec.ina_nattxs + sec.ina_navv1p8 + sec.ina_Nav1_3 + sec.ina_nakpump)
        else:
            sec.gnaleak_leak = -(sec.ina_nattxs + sec.ina_navv1p8 + sec.ina_Nav1_3 + sec.ina_nakpump) / (vinit - sec.ena)

        if ((-(sec.ik_kdr + sec.ik_nakpump + sec.ik_kap + sec.ik_kad) / (vinit - sec.ek)) < 0):
            sec.pumpik_extrapump = -(sec.ik_kdr + sec.ik_nakpump + sec.ik_kap + sec.ik_kad)
        else:
            sec.gkleak_leak = -(sec.ik_kdr + sec.ik_nakpump + sec.ik_kap + sec.ik_kad) / (vinit - sec.ek)

def simulate(cell, tstop=200, vinit=-55):
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

def show_output(branch_v_vec, stimsec_v_vec, t_vec, new_fig=True):
    if new_fig:
        pyplot.figure(figsize=(8,4)) # Default figsize is (8,6)
    soma_plot = pyplot.plot(t_vec, branch_v_vec, color='red')
    dend_plot = pyplot.plot(t_vec, stimsec_v_vec, color='black')
    pyplot.legend(soma_plot + dend_plot, ['branch', 'stimsec'])
    pyplot.xlabel('time (ms)')
    pyplot.ylabel('mV')

cell = cfiber()
for sec in h.allsec():
    h.psection(sec=sec)
branch_v_vec, stimsec_v_vec, t_vec = set_recording_vectors(cell)
simulate(cell)
show_output(branch_v_vec, stimsec_v_vec, t_vec)
pyplot.show()