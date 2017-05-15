# Memristive brain architecture

Starting idea of the memristive brain project: implement emotional pathways of a mammalian brain biomimetically  reproducing cortical and subcortical structures of a mammalian brain. Previously we have used "cube of emotions" by Hugo Lövheim to as the base for the emotional simulation for the reimplementation of psycho-emotional states of a mammal in a computational system, see our project [NeuCogAr](https://github.com/research-team/NEUCOGAR). The "cube of emotions" is based on three monoamine neuromodulators: dopamine (DA), noradrenaline (NA) and serotonin (5HT).

## Component diagram

As the part of [Robot Dream architecture](architecture.md) the memristive brain component takes central role in a robotic system, for exhaustive description of other than memristive brain components see [architectural documentation](architecture.md) 

![Memristive brain HLD component diagram](HLD_Component_Memristive_Robot.png)

## Initial ideas

The initial idea was to start with dopaminergic pathways of mammals, for example nigrostriatal pathway as possibly most basic and simplest pathway among others of DA, NA and 5HT pathways. 

![Simplified diagram of nigrostriatal pathway](nigrostriatal.png)

This pathway works in balance of excitation/inhibition as well there is influence of the dopamine neuromodulation over striatal D1 and D2 receptors.

This is implemented dopamine pathways in the [NeuCogAr project](https://github.com/research-team/NEUCOGAR).

![Dopamine pathways implemented in NeuCogAr](https://raw.githubusercontent.com/research-team/NEUCOGAR/master/NEST/cube/dopamine/integrated/doc/diagram.png)

## Initial requirements

The memristive solution should be capable of key processes of a mammalian brain involved in psycho-emotional processing:

1. Excitatory 
1. Inhibitory 
1. Neuromodulatory 

## Memristive neuron

As the starting point we have selected the implementation of inhibitory impact over neuronal processes in memristive hardware implementation. 

![Block diagram](HL_Emristor.png)



## Neuromodulation

We plan to implement the [G-Protein](https://en.wikipedia.org/wiki/G_protein%E2%80%93coupled_receptor) signalling [pathway principles](https://en.wikipedia.org/wiki/Signal_transduction) in hardware based on memristive elements. 


