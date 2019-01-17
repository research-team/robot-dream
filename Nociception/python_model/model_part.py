from neuron import h, gui
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pyplot
neuron.load_mechanisms("/Users/sulgod/Desktop/Nociception/newproj/mod")

class BallAndStick(object):
    def create_sections(self):
        self.soma = h.Section(name='soma', cell=self)
        self.dend = h.Section(name='dend', cell=self)
    def build_topology(self):
        self.dend.connect(self.soma(1))
    def define_geometry(self):
        self.soma.L = self.soma.diam = 12 # microns
        self.dend.L = 250                      # microns
        self.dend.diam = 1                     # microns
        self.dend.nseg = 4
        h.define_shape() # Translate into 3D points.
    def define_biophysics(self):
        for sec in self.all: # 'all' defined in build_subsets
            sec.Ra = 100    # Axial resistance in Ohm * cm
            sec.cm = 1      # Membrane capacitance in micro Farads / cm^2
        self.soma.insert('hh')
        self.soma.gnabar_hh=0.25
        self.soma.gl_hh = .0002
        self.soma.el_hh = -60.0
        self.soma.gkbar_hh = 0.36
        self.dend.insert('na17a')
        self.dend.insert('nap')
        self.dend.insert('nafast')
        self.dend.insert('naslow')
        self.dend.insert('kv')
        self.dend.insert('kdr0')
        self.dend.insert('kad')
        self.dend.insert('kap')
        self.dend.gbar_na17a = 15.2
        self.dend.gbar_nap = 0.0002
        self.dend.gbar_nafast = 0.05
        self.dend.gbar_naslow = 0.02
        self.dend.gbar_kv = 60
        self.dend.gbar_kdr0 = 0.2
        self.dend.gbar_kad = 0.3
        self.dend.gbar_kap = 0.25	
    def build_subsets(self):
        self.all = h.SectionList()
        self.all.wholetree(sec=self.soma) 
    def __init__(self):
        self.create_sections()
        self.build_topology()
        self.build_subsets()
        self.define_geometry()
        self.define_biophysics()

def set_recording_vectors(cell):
    soma_v_vec = h.Vector()   # Membrane potential vector at soma
    dend_v_vec = h.Vector()   # Membrane potential vector at dendrite
    t_vec = h.Vector()        # Time stamp vector
    soma_v_vec.record(cell.soma(0.5)._ref_v)
    dend_v_vec.record(cell.dend(0.5)._ref_v)
    t_vec.record(h._ref_t)
    return soma_v_vec, dend_v_vec, t_vec

def simulate(tstop=25, vinit=-72):
    h.tstop = tstop
    h.v_init = vinit
    h.run()

def show_output(soma_v_vec, dend_v_vec, t_vec, new_fig=True):
    if new_fig:
        pyplot.figure(figsize=(8,4)) # Default figsize is (8,6)
    soma_plot = pyplot.plot(t_vec, soma_v_vec, color='red')
    dend_plot = pyplot.plot(t_vec, dend_v_vec, color='black')
    pyplot.legend(soma_plot + dend_plot, ['soma', 'dend(0.5)'])
    pyplot.xlabel('time (ms)')
    pyplot.ylabel('mV')

cell = BallAndStick()
diff = h.AtP_4(cell.dend(0.5))
rec = h.p2x3(cell.dend(0.5))
diff.h = 0.1
diff.tx1 = 10
rec.Ev = -40
h.setpointer(diff._ref_atp, 'patp', rec)
for sec in h.allsec():
    h.psection(sec=sec)
soma_v_vec, dend_v_vec, t_vec = set_recording_vectors(cell)
simulate()
show_output(soma_v_vec, dend_v_vec, t_vec)
pyplot.show()
#pyplot.savefig('/Users/sulgod/Desktop/Nociception/onespike.pdf')

