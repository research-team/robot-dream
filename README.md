# Robot dream project

## Problem

The project is dedicated to the integration of the simulated mammalian brain developed in [NeuCogAr project](https://github.com/research-team/neucogar) with robotic embodiment. One of the options of robotic embodiment is presented by the [Memristive brain project](https://github.com/research-team/memristive-brain).

During the [NeuCogAr](https://github.com/research-team/neucogar) project we have managed to reimplement several basic emotinal states: fear-like, disgust-like based on two dopamine and serotonin subsystems. Later we have added noradrenaline subsystem completely implementing the ["cube of emotions" by Hugo Lövheim](https://en.wikipedia.org/wiki/L%C3%B6vheim_cube_of_emotion).

The simulated brain with emotional drives needs the embodiment to have an interface with the real world with all the complexity and variety of inbound stimula. We could not put the cluster based simulation that is not real time into the robotic embodiment with the computational capacity similar to one notebook. To solve the computational capacity gap problem we have introduced the two phases approach.
The working metaphor is the dreaming and wake phase of a mammalian life. 

![High level architecture](https://raw.githubusercontent.com/research-team/robot-dream/master/doc/HL_Life_cycle.png)

During the wake phase a robotic system acts in realtime and stores the inbound stimula and managing actuators signals in the form of pseudoneuronal activity. Later the pseudoneuronal activity is transferred to the HPC cluster with the simulated dreaming brain. The dreaming brain processes the inbound information updates the synapses of the simulated neuronal circuits. Later updated behavioral strategies are transferred back to the robotic embodiment system.

One of the prossible solutions for the robotic system is represented in the [Memristive brain project]() dedicated to the implementation of bio-plausible approarch for the neuron and neuronal circuits implemeantation using electronic memristive schematic with inhibition and neuromodulation functions.

The artcile with architecture desription could be found [here](http://arxiv.org/abs/1603.03007)

The complete architectural documentation could be found [here](/doc/architecture.md)

## Breakthrough

**Robotics and cognitive architectures** - first time the bio-plausible emotional driven cognitive architecture integrated with robotics embodiment will be demonstrated with sensory input and motor output neural systems.

