import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as pyplot

spike_times = [[] for i in range(20)]
with open('out.spk') as f:
    for line in f:
        vals = line.split()
        spike_times[int(vals[1])].append(float(vals[0]))
for i, spikes in enumerate(spike_times):
    pyplot.vlines(spikes, i + 0.5, i + 1.5, color='black')
pyplot.show()