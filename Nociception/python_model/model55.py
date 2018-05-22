from neuron import h, gui
from matplotlib import pyplot
neuron.load_mechanisms("/Users/sulgod/Desktop/Nociception/newproj/mod")
soma = h.Section(name='soma')
dend = h.Section(name='dend')
dend.connect(soma(1))
h.topology()
soma.diam=soma.L=18
dend.diam=1
dend.L=250
for sec in h.allsec():
    sec.Ra = 100    # Axial resistance in Ohm * cm
    sec.cm = 1      # Membrane capacitance in micro Farads / cm^2
soma.insert('hh')
soma.gnabar_hh=0.25
soma.gl_hh = .0002
soma.el_hh = -60.0
soma.gkbar_hh = 0.36
dend.insert('na17a')
dend.insert('nap')
dend.insert('nafast')
dend.insert('naslow')
dend.insert('kv')
dend.insert('kdr0')
dend.insert('kad')
dend.insert('kap')
dend.gbar_na17a = 15.2
dend.gbar_nap = 0.0002
dend.gbar_nafast = 0.05
dend.gbar_naslow = 0.02
dend.gbar_kv = 60
dend.gbar_kdr0 = 0.12
dend.gbar_kad = 0.3
dend.gbar_kap = 0.25
#diff = h.AtP_4(dend(0.5))
#rec = h.p2x3(dend(0.5))
#diff.h = 0.1
#diff.tx1 = 10
#rec.Ev = -40
#h.setpointer(diff._ref_atp, 'patp', rec)	
for sec in h.allsec():
    h.psection(sec=sec)
v_vec = h.Vector()             # Membrane potential vector
t_vec = h.Vector()             # Time stamp vector
v_vec.record(dend(0.5)._ref_v)
t_vec.record(h._ref_t)
h.tstop = 25.0
h.v_init = -72.0
h.run()
pyplot.figure(figsize=(8,4)) # Default figsize is (8,6)
pyplot.plot(t_vec, v_vec)
pyplot.xlabel('time (ms)')
pyplot.ylabel('mV')
pyplot.show()
