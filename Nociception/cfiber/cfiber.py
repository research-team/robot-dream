from neuron import h, gui
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pyplot
neuron.load_mechanisms("./mod")

class cfiber(object):
    def create_sections(self):
        self.stimsec = h.Section(name='stimsec', cell=self)
        self.branch = h.Section(name='branch', cell=self)
        '''
        self.cone = h.Section(name='cone', cell=self)
        self.parent = h.Section(name='parent', cell=self)
        self.endsec1 = h.Section(name='endsec1', cell=self)
        self.endsec2 = h.Section(name='endsec2', cell=self)
        '''
        #self.soma = h.Section(name='soma', cell=self)
        #self.dend = [h.Section(name='dend[%d]' % i) for i in range(10)]
    def build_topology(self):
        self.stimsec.connect(self.branch(0), 1)
        #self.branch.connect(self.cone(0), 1)
        '''
        self.cone.connect(self.parent(0), 1)
        self.parent.connect(self.endsec1(0), 1)
        self.endsec1.connect(self.endsec2(0), 1)
        #self.dend[0].connect(self.soma(1), 0)
        '''
        #for i in range(1, len(self.dend)):
        #    self.dend[i].connect(self.dend[i-1], 1)
    def define_geometry(self):
        self.stimsec.L = 400
        self.stimsec.diam = 0.25
        self.stimsec.nseg = 1
        self.branch.L = 1000
        self.branch.diam = 0.25
        self.branch.nseg = 10
        '''
        self.cone.L = 5000
        self.cone.diam = 0.25
        self.cone.nseg = 100
        self.parent.L = 10000
        self.parent.diam = 1
        self.parent.nseg = 200
        self.endsec1.L = 100
        self.endsec1.diam = 1
        self.endsec1.nseg = 10
        self.endsec2.L = 100
        self.endsec2.diam = 1
        self.endsec2.nseg = 10
        '''

        '''
        self.soma.L = self.soma.diam = 12 # microns
        for sec in self.dend:
            sec.L = 250   # microns
            sec.diam = 1  # microns
            sec.nseg = 5
        '''
        h.define_shape() # Translate into 3D points.
    def define_biophysics(self):
        for sec in self.all: # 'all' defined in build_subsets
            sec.Ra = 35    # Axial resistance in Ohm * cm
            sec.cm = 1      # Membrane capacitance in micro Farads / cm^2
            sec.insert('na17a')
            sec.insert('nav1p8')
            sec.insert('nap')
            sec.insert('nafast')
            sec.insert('naslow')
            sec.insert('extrapump')
            sec.insert('h')
            sec.insert('koi')
            sec.insert('naoi')
            sec.insert('kna')
            sec.insert('nakpump')
            sec.insert('nav1p9')
            sec.insert('nattxs')
            sec.insert('kf')
            sec.insert('ks')
            sec.insert('kdr')
            sec.insert('kad')
            sec.insert('kap')
            sec.insert('leak')
            sec.gbar_na17a = 0.1066439
            sec.gbar_nav1p8 = 0.14271
            sec.gbar_nap = 0.0002
            sec.gbar_nafast = 0.02
            sec.gbar_naslow = 0.01
            sec.gbar_kdr = 0.018002
            sec.gbar_kad = 0.95
            sec.gbar_kap = 0.95	
            sec.gbar_ks = 0.0#069733
            sec.gbar_kf = 0.0#12756
            sec.gbar_h = 0.0#25377
            sec.gbar_nattxs = 0.0#10664
            sec.gbar_nav1p9 = 0#9.4779e-5
            sec.smalla_nakpump = -0.047891
            sec.gbar_kna = 0.0#0042
            sec.theta_naoi = 0.045
            sec.theta_koi = 0.045
            sec.celsiusT_ks = 37
            sec.celsiusT_kf = 37
            sec.celsiusT_h = 37
            #sec.celsiusT_nattxs = 37
            sec.celsiusT_nav1p8 = 37
            #sec.celsiusT_nav1p9 = 37
            sec.celsiusT_nakpump = 37
            sec.celsiusT_kdr = 37
    def build_subsets(self):
        self.all = h.SectionList()
        for sec in h.allsec():
            self.all.append(sec=sec)    
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
    soma_v_vec.record(cell.branch(0.5)._ref_v)
    dend_v_vec.record(cell.stimsec(0.5)._ref_v)
    t_vec.record(h._ref_t)
    return soma_v_vec, dend_v_vec, t_vec

def balance(cell, vinit=-55):
    for sec in cell.all:
        if ((-(sec.ina_nattxs + sec.ina_nav1p9 + sec.ina_nav1p8 + sec.ina_na17a + sec.ina_nap + sec.ina_nafast + sec.ina_naslow + sec.ina_h + sec.ina_nakpump) / (vinit - sec.ena)) < 0):
            sec.pumpina_extrapump = -(sec.ina_nattxs + sec.ina_nav1p9 + sec.ina_nav1p8 + sec.ina_na17a + sec.ina_nap + sec.ina_nafast + sec.ina_naslow + sec.ina_h + sec.ina_nakpump)
        else:
            sec.gnaleak_leak = -(sec.ina_nattxs + sec.ina_nav1p9 + sec.ina_nav1p8 + sec.ina_na17a + sec.ina_nap + sec.ina_nafast + sec.ina_naslow + sec.ina_h + sec.ina_nakpump) / (vinit - sec.ena)

        if ((-(sec.ik_ks + sec.ik_kf + sec.ik_h + sec.ik_kdr + sec.ik_nakpump + sec.ik_kna + sec.ik_kap + sec.ik_kad) / (vinit - sec.ek)) < 0):
            sec.pumpik_extrapump = -(sec.ik_ks + sec.ik_kf + sec.ik_h + sec.ik_kdr + sec.ik_nakpump + sec.ik_kna + sec.ik_kap + sec.ik_kad)
        else:
            sec.gkleak_leak = -(sec.ik_ks + sec.ik_kf + sec.ik_h + sec.ik_kdr + sec.ik_nakpump + sec.ik_kna + sec.ik_kap + sec.ik_kad) / (vinit - sec.ek)

def simulate(cell, tstop=104, vinit=-55):
    h.finitialize(vinit)
    balance(cell)
    if h.cvode.active():
        h.cvode.active()
    else:
        h.fcurrent()
    h.frecord_init()
    print(cell.stimsec.gnaleak_leak)
    h.tstop = tstop
    h.v_init = vinit
    h.run()

def show_output(soma_v_vec, dend_v_vec, t_vec, new_fig=True):
    if new_fig:
        pyplot.figure(figsize=(8,4)) # Default figsize is (8,6)
    soma_plot = pyplot.plot(t_vec, soma_v_vec, color='red')
    dend_plot = pyplot.plot(t_vec, dend_v_vec, color='black')
    pyplot.legend(soma_plot + dend_plot, ['branch', 'stimsec'])
    pyplot.xlabel('time (ms)')
    pyplot.ylabel('mV')

cell = cfiber()
diff = [h.AtP_4(cell.stimsec(0.1)) for i in range(10)]
rec = [h.p2x3(cell.stimsec(0.1)) for i in range(10)]
for i in range(10):
    diff[i].h = 0.01
    diff[i].Deff = 0.08
    diff[i].tx1 = 10 + 100*i
    rec[i].Ev = 7
    rec[i].gmax = 6
    h.setpointer(diff[i]._ref_atp, 'patp', rec[i])
for sec in h.allsec():
    h.psection(sec=sec)
soma_v_vec, dend_v_vec, t_vec = set_recording_vectors(cell)
simulate(cell)
show_output(soma_v_vec, dend_v_vec, t_vec)
pyplot.show()