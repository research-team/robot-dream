from neuron import h, gui
import math
import random
#neuron.load_mechanisms("./mod")

class cfiber(object):
    '''
    C-fiber class with parameters:
    L: int (mkM)
        length of compartment
    d: float 
        diameter of fiber
    num: int
        number of compartments
    coordinates: dict (updates by position())
        coordinates of each section
    zpozition: int 
        z - coordinate for few cells simulation
    fast_diff: bool
        Is there fast diffusion?
          -Yes: True 
          -No: False
    diffs: list
        list of diffusion mechanisms (NEURON staff)
    recs: list
        list of receptors mechanisms (NEURON staff)
    '''      
    def __init__(self, L, d, zpozition, x_application, fast_diff, numofmodel):
        self.coordinates = dict()
        self.distances = dict()
        self.diffusions = dict()
        self.fast_diff = fast_diff
        self.diffs = []
        self.recs = []
        self.L = L
        self.diam = d
        self.zpozition = zpozition
        self.x_application = x_application
        self.numofmodel = numofmodel
        if self.numofmodel == 11 or self.numofmodel == 12:
            self.num = 170
        else:
            self.num = 120
        self.create_sections()
        self.build_topology()
        self.build_subsets()
        self.define_geometry()
        self.position()
        self.distance()
        self.define_biophysics()
    def create_sections(self):
        '''
        Creates sections (compartments)
        '''
        self.branch = h.Section(name='branch', cell=self)
        self.stimsec = [h.Section(name='stimsec[%d]' % i) for i in range(self.num)]
    def build_topology(self):
        '''
        Connects sections 
        '''
        self.stimsec[0].connect(self.branch(0), 1)
        if self.numofmodel == 11 or self.numofmodel == 12:
            for i in range(1, 70):
                self.stimsec[i].connect(self.stimsec[i-1])
            for i in range(70, 120):
                self.stimsec[i].connect(self.stimsec[i-1])
            for i in range(120, 170):
                self.stimsec[i].connect(self.stimsec[i-1])
            self.stimsec[70].connect(self.stimsec[69])
            self.stimsec[120].connect(self.stimsec[69])
        else:
            for i in range(1, len(self.stimsec)):
                self.stimsec[i].connect(self.stimsec[i-1])
    def define_geometry(self):
        '''
        Adds length and diameter to sections
        '''
        for sec in self.stimsec:
            sec.L = self.L# microns
            sec.diam = self.diam # microns
        self.branch.L = self.L
        self.branch.diam = self.diam
        self.branch.nseg = 1
        h.define_shape() # Translate into 3D points.
    def position(self):
        '''
        Adds 3D position 
        '''
        if self.numofmodel == 11 or self.numofmodel == 12:
            h.pt3dclear()
            h.pt3dadd(0, 0, self.zpozition, self.diam)
            h.pt3dadd(self.L, 0, self.zpozition, self.diam)
            xyz = dict(x=self.L, y=0, z=0)
            self.coordinates.update({self.branch: xyz})
            for i in range(70):
                h.pt3dclear()
                h.pt3dadd(self.L*(i+1), 0, self.zpozition, self.diam)
                h.pt3dadd(self.L*(i+2), 0, self.zpozition, self.diam)
                xyz = dict(x=self.L*(i+2), y=0, z=0)
                self.coordinates.update({self.stimsec[i]: xyz})
            for i in range(70, 120):
                h.pt3dclear()
                h.pt3dadd(self.L*(i+1), i*8, self.zpozition, self.diam)
                h.pt3dadd(self.L*(i+2), (i+1)*8, self.zpozition, self.diam)
                xyz = dict(x=self.L*(i+2), y=(i+1)*8, z=0)
                self.coordinates.update({self.stimsec[i]: xyz})
            for i in range(120, 170):
                h.pt3dclear()
                h.pt3dadd(self.L*(i+1), i*(-8), self.zpozition, self.diam)
                h.pt3dadd(self.L*(i+2), (i+1)*(-8), self.zpozition, self.diam)
                xyz = dict(x=self.L*(i+2), y=(i+1)*(-8), z=0)
                self.coordinates.update({self.stimsec[i]: xyz})
        else:
            i = 0
            for sec in self.all:
              h.pt3dclear()
              h.pt3dadd(self.L*i, 0, self.zpozition, self.diam)
              h.pt3dadd(self.L*(i+1), 0, self.zpozition, self.diam)
              xyz = dict(x=self.L*(i+1), y=0, z=0)
              self.coordinates.update({sec: xyz})
              i+=1
    def distance(self):
        '''
        Adds distances from application for every compartment 
        '''
        #self.distances.clear()
        for compartment in self.all:
            distance = math.sqrt((self.x_application-self.coordinates.get(compartment).get('x'))**2 + (50-self.coordinates.get(compartment).get('y'))**2 + (0.01-self.coordinates.get(compartment).get('z'))**2)
            self.distances.update({compartment: distance})
    def define_biophysics(self):
        '''
        Adds channels and their parameters 
        '''
        for sec in self.all: # 'all' defined in build_subsets
            sec.Ra = 35  # Axial resistance in Ohm * cm
            sec.cm = 1      # Membrane capacitance in micro Farads / cm^2
            sec.insert('navv1p8')
            sec.insert('extrapump')
            sec.insert('koi')
            sec.insert('naoi')
            sec.insert('nakpump')
            sec.insert('nattxs')
            sec.insert('kdr')
            sec.insert('kad')
            sec.insert('kap')
            sec.insert('leak')
            sec.insert('Nav1_3')
            sec.insert('extracellular')
            if self.numofmodel == 8 or self.numofmodel >= 11:
                sec.gbar_navv1p8 = 0.2
            elif self.numofmodel == 7:
                sec.gbar_navv1p8 = 0.1
            else:
                sec.gbar_navv1p8 = 0
            sec.gbar_kdr = 0.01
            sec.gbar_kad = 0.1
            sec.gbar_kap = 0.1
            if self.numofmodel == 6:
                sec.gbar_nattxs = 0.2
            else:
                sec.gbar_nattxs = 0.1
            sec.gbar_Nav1_3 = 0.2
            sec.smalla_nakpump = -0.0047891
            sec.theta_naoi = 0.029
            sec.theta_koi = 0.029
            sec.celsiusT_nattxs = 37
            sec.celsiusT_navv1p8 = 37
            sec.celsiusT_nakpump = 37
        for sec in self.stimsec:
            # self.add_P2Xreceptors(sec, 10, 12)
            self.add_5HTreceptors(sec, 10, 9)
            # self.add_5HTreceptors(sec, 80, 3)            
    def add_P2Xreceptors(self, compartment, time, g):
        '''
        Adds P2X3 receptors
        Parameters
        ----------
        compartment: section of NEURON cell
            part of neuron 
        x: int
            x - coordinate of ATP application
        time: int (ms)
            time of ATP application
        g: float
            receptor conductance 
        '''
        if self.fast_diff:
            diff = h.AtP_42(compartment(0.5))
            diff.h = self.distances.get(compartment)
            diff.tx1 = time
            diff.Deff = 0.8
            diff.c0cleft = 1
            if self.numofmodel == 1:
                diff.k = 0
            else:
                diff.k = 0.01
        else:
            diff = h.AtP_slow(compartment(0.5))
            diff.h = self.distances.get(compartment)
            diff.tx1 = time + 0 + (diff.h/1250)*1000
            diff.c0cleft = 100
        self.diffusions.update({diff: compartment})
        rec = h.p2x3(compartment(0.5))
        rec.gmax = g
        rec.Ev = 5
        # rec2 = h.p2x2(compartment(0.5))
        # rec2.gmax = g/2
        # rec2.Ev = -7
        h.setpointer(diff._ref_atp, 'patp', rec)
        # h.setpointer(diff._ref_atp, 'patp', rec2)
        self.recs.append(rec)
        self.diffs.append(diff)
        # self.recs.append(rec2)
    def add_5HTreceptors(self, compartment, time, g):
        '''
        Adds 5HT receptors
        Parameters
        ----------
        compartment: section of NEURON cell
            part of neuron 
        x: int
            x - coordinate of serotonin application
        time: int (ms)
            time of serotonin application
        g: float
            receptor conductance 
        '''
        if self.fast_diff:
            diff = h.diff_5HT(compartment(0.5))
            diff.h = self.distances.get(compartment)
            diff.tx1 = time
            if self.numofmodel == 14:
                diff.a = 100
            else:
                diff.a = 0
            diff.Deff = 0.004
            diff.c0cleft = 3
        else:
            diff = h.slow_5HT(compartment(0.5))
            diff.h = self.distances.get(compartment)
            diff.tx1 = time + 0 + (diff.h/50)*1000
            diff.c0cleft = 3
        rec = h.r5ht3a(compartment(0.5))
        rec.gmax = g
        h.setpointer(diff._ref_serotonin, 'serotonin', rec)
        self.diffs.append(diff)
        self.recs.append(rec)      
    def build_subsets(self):
        '''
        adds sections in NEURON SectionList
        '''
        self.all = h.SectionList()
        for sec in h.allsec():
          self.all.append(sec=sec)  
    def connect2target(self, target):
        '''
        Adds presynapses 
        Parameters
        ----------
        target: NEURON cell
            target neuron 
        Returns
        -------
        nc: NEURON NetCon
            connection between neurons
        '''
        nc = h.NetCon(self.branch(1)._ref_v, target, sec = self.branch)
        nc.threshold = 10
        return nc