# Robot Dream architecture

## Problem

Rather than implementing the
emotional model in a computational system, we re-implemented the neurobiological
basis of emotions using simulation [30]. This was done to create a biologically
plausible approach and to validate the results of our simulations from neurobiological
perspective. The other way around could not provide proper evidence that
the result could be regarded as emotional phenomenon. We used the model of
basic mechanisms of a mammalian brain via neuromodulation and their mapping
to basic affective states [14, 26, 27, 28, 29]. We used the realistic spiking neural
networks with neuromodulation reconstructing all brain structures involved into
the pathways of neuromodulators of the “cube of emotions” by Hugo Lövheim
[14]. Unfortunately, current robotic systems usually do not have enough memory
and computational capacity to run realistic simulations of human brain activity.

For example, this is computational resources of rather advanced bipedal
robotic platform AR-601:

* CPU — 4th Gen Intel Core i7-4700EQ 4-Core 3.4GHz processor;
* System Memory — 1 x204-Pin DDR3L 1333MHz SO-DIMM up to 8 GB;

However the simulation of 1% of human brain required a cluster of 250 K-
supercomputers (each contains 96 computing nodes, each node contains a 2.0
GHz 8-core SPARC64 processor and 16 GB of memory) that was done by RIKEN
institute in 2013 and this simulation was slower than human brain in 1000 times
[12]. According to the estimates of the Human brain project the computational
capacity to simulate whole human brain should be 30 exaflop that is not feasible
at the moment.

A realistic simulation even for parts of mammalian brain involved
into neuromodulation processes leading to emotional reactions cannot be done in
real-time even at scale of rat brain (not mention human brain) on an autonomous
robotic platform. To combine autonomous control with advanced realistic emotional
appraisal we propose life-cycle separation into “day” and “night” phases.

## High level overview

### Life cycle ("dream-wake" cycle)

![High level overview](HL_Life_cycle.png)
Overall robotic system life-cycle is divided into two phases: *wake* (day) and *dream* (night).

- [**a**] In this position a robotic system transfers the accumulated during *wake* phase experience into spiking neural network of the *dreaming brain*.
- [**b**] Processing of *dreaming phase* is done as follows:
  - The accumulated experience is transferred from a robotic system to the dreaming brain;
  - Then simulation starts producing a set of updated rules to a robotic system;
  - Finally update is transferred to a robotic system.
- [**c**] The updated behavior strategies is transferred to a robotic system and applied to it.
- [**d**] The robotic system continues it's wake phase with updated control system strategies, adjusted emotional reactions and accumulating new experience, storing all sensory inputs, to be processed again starting from **a**.

### Training 

We propose to use mammalian dream analogy for the training process either.
During the "maturation" "wake-dream" cycles should become more inclined towards "wake" phase but originally the system should be more "dreaming" rather than actively acting. The purpose of this "dream-wake" balancing is to provide more frequent thus intensive "dreaming" rather than acting to adapt and update the rule-based system to the real world environment.

One of possibles scenario could be that originally the robotic system should not have any preset (instinctive) rules. If the robotic system receives any painful feedback (for example hits the wall) it should be unable to react accordingly to situation. During "dreaming" phase the "dreaming brain" that should not have any preset reaction should try any random motor reaction that in its turn should be translated as rule to the robotic system. The robotic system will use this action: if this reaction reduces the pain the robotic system registers the "pain relief". The "pain relief" translated into the "dreaming brain" triggers the reward system that in its turn reinforce the association of painful sensory input with the action. On the other hand if the action does not lead to "pain relief" the pain sensory input persist and is still been translated into the "dreaming brain". The dreaming brain should try other random action and the whole "robot dream" should repeat the cycle of "dream-wake".

The other possible option could be: the robotic system would have predefined (instinctive) rules, that should be translated into neuronal structures of the "dreaming brain". This way we should use "bisimulation" approach described in our article: "Robot Dream" to adapt the "dreaming brain" first to the instinctive rules.

### Translations

![High level translations](HL_Translations.png)

The **direct translation** is done in the playback mode similar to a mammalian brain processing of the wake experience. This way whole wake experience should be translated to the sequence of dreaming brain neurons activations based on the semantics of an inbound signals, for example the activations of tactile sensors should be translated into activations of sensory cortex, audio signals should be translated into auditory cortex neurons activations.

![High level reverse translation](HLD_Activity_Reverse_translation.png)

The **reverse translation** is gradual step by step process that could be divided into several phases:

- Increase of abstraction layer and generalize the "**dreaming brain**" spiking neural network (**sNN**) connections
- Translation of the **sNN** of the "**dreaming brain**" into rule based description of the behavior strategies of a robotic system
- Validation of translation steps
- Validation of overall reverse translation process
- Transfer of rule based behavior strategies into a robotic system.


Overall translation validation is based on overall statistical analysis of the semantically tagged sNN of a dreaming brain highlighting most important neuronal connections using [**semantic tagging**](architecture.md#semantictagger) to the key concepts.

## HLD

### Use cases

![Use cases](HLD_Use_cases.png)

There are three main types of use cases:

1. Live
1. Translate
  2. Direct
  2. Reverse

The **living** use case is denoting the ordinary life-cycle of a robotic system or dreaming brain. For a robotic system usually consists of real time acting based on updated behavior strategies storing the daily experience with semantic highlighting: object and action tagging, pleasure and pain tagging.

The **translation** use case is denoting the transfer and processing the original stored experience of a robotic system into the form of neural network activity and from neural network into robotic system rules. The **direct** translation in the form of playback of the **wake** phase experience in form of neuronal activity of a dreaming brain, the **reverse** process the updated sNN of a dreaming brain in to rules of a robotic system.

### Activity

![High level design activity diagram](HLD_Activity_life_cycle.png)

Overall the robot to the dreaming brain synchronization life-cycle.
- "**Wake phase**"
  - Firstly the robotic system stores the experience of every sensory channel, including pleasure and pain tags.
  - During the **direct translation** the robotic system transmits the stored information to the **dreaming brain**.
- "**Dreaming phase**"
  - The **dreaming brain** plays back the transmitted experience by means of spiking neuronal network  (sNN) neurons activation (translating).
  - The **dreaming brain** runs the simulation life-cycle updating the sNN.
  - During the **reverse translation** the **dreaming brain** runs the number of activities to translate the updated structure of sNN into rules of behavioral strategies of the robotic system.
  - The robotic system updates behavioral strategies and runs the real-time or semi real-time life-cycle, storing new experience.

 Practically speaking the dreaming phase of the dreaming brain and the wake phase of the robotic system could overlap and process simultaneously.

### Components

#### Robot
![High level design components of robot life cycle](HLD_Component_RobotLifeCycle.png)

This is a high-level representation of the overall structure of the robotic control system.
The control system might be embedded into robotic platform of executed on remote
machine wirelessly communicating with the robot.

The **RobotLifeCycle** component provides proper functions for real-time operation
of a robotic system via the **RuleBasedSystem** including storage of the **wake** phase experience and translation
into the **dreaming brain**.

The **DriverInterface** is responsible for communication with the underlying
hardware platform. It translates abstract commands into concrete ones for particular
robotic system.

The central part of the system is a cognitive architecture implementation.
The component is named **ModelOfSix** as we adopt "model of six" proposed by Marvin Minsky.
It contains six interconnected behavioral layers: instinctive, learned, deliberative,
reflective, self-reflective and self-conscious. Each layer implements appropriate
rules-based inference adopting if-do-then rules.

During its course of operation robotic system records inbound information for later
transmission to the **dreaming brain**. **ExperienceStorage** component keeps all
this data until **DirectTransmitter** transfers it to a supercomputer.


##### DirectTransmitter (Direct translation)

Transfer of the stream of stored and tagged experience from the robotic system into
the dreaming brain.

For transmission of signals we're adopting Neuralynx file format. For further
details please consult [this description](direct_translation_format.md).


##### RuleBasedSystem (Robot life cycle)

The temporal probabilistic rules system, probably [NARS](https://github.com/opennars/opennars/wiki).

...

#### DreamingBrain

![High level design components of the "dreaming brain"](HLD_Component_SleepingBrainLifeCycle.png)

The high-level representation of overall structure of the **DreamingBrain**.

##### Direct translation

The **ExperienceTranslator** includes **ExperiencePlayer** that translates different types of tagged inbound sensory inputs transferred from robotic system into neuronal activities of sNN of the dreaming brain in the form of synchronous playback of neuronal activations based on wiring of sensory channel to the dreaming brain area.

##### SemanticTagger

Semantic tagging is the association process of several sensory inputs channels using temporal window.
A robotic system tags time frames, and if possible objects in different input channels based on detected tagging events building associations in a forms of semantic clustering. Tagging events could be:

- pleasure and pain stimulus
- detected visual object: banana, battery, bright flash light, human figure, etc
- detected audio signal: loud sound, word, etc
- sensory stimulus

Different sensory tagged are translated into tagged neuronal structures of the sNN of the dreaming brain during the direct translation phase.

![Semantic tagger activity](HLD_Activity_SemanticTagger.png)

##### Reverse translation

The **ReverseTranslator** component is responsible for the translation of neuronal structures and activities or the dreaming brain into the robotic system **RuleBasedSystem**. The translation process could be divided into principal phases:

- rising abstraction layer or the sNN of the "**dreaming brain**" reducing computational load making sNN operate in sub-real-time mode done by **DreamingBrainLifeCycle**
- generalization and convolution neuronal structures into rules of the robotic system **RuleBasedSystem** via **GeneralisationStrategy** and its components: **Narrative**, **Induction**, **Abduction**, **OntologyBased**.
- generalization and convolution are gradual stepwise processes that include 2 types of validation: **StepValidator** and overall **OverallValidator**.

##### DreamingBrainLifeCycle:Rise of abstraction layer of the sNN

The granularity level of the sNN could be switched in several ways for example instead of Hodgkin–Huxley model the integrate and fire could be used.
The other way is to take in account events of a different time scale: **spikes** and electro-chemical activity including changes of conductance, resistance, current and potential in the **milliseconds** timescale; spike timing plasticity (excitatory, inhibitory) in the **seconds** timescale; long term as well as structural plasticity in the **hours** timescale.

<!-- ![Rise of abstraction layer](WP_20160729_001.jpg) -->

##### GeneralisationStrategy:Narrative

The narrative is the form of generalization of logical rules and neuronal circuits into logical rules based on temporal sequential patterns.
The sequential neuronal pattern could be generalized into form of higher level concept or and consequent of the pattern activation.
From the perspective of temporal logical rules the sequence of logical patterns could be generalized in the form of logical inference final consequent. The narrative could be understood as form of clustering of neuronal pattern circuits in high-level abstractions as well as sequential patterns of temporal [probabilistic] logic in high-level logical concepts.

##### ExperiencePlayer:Pleasure and pain

According to the dissertation "Neurocomputational Mechanisms for Adaptive Self-Preservative Robot Behaviour" by Nicolás Ignacio Navarro Guerrero, the main structures involved in pain processing: PFC, VTA, thalamus, amygdala, PAG, RRF, hippocampus. These structures are implemented in the [NeuCogAr project](https://github.com/research-team/neucogar). For the detailed description of pleasure and pain via nociception see chapter 6, for the detailed description of fear conditioning see chapter 7 of the dissertation.


##### Validator

During the **reverse translation** phase these pattern and circuits are generalized into high-level logical rules via mechanisms described above.
The number of representations of objects is reduced, but the **StepValidator** tracks the adequacy of processing via selecting most important according to the number of tagged connections events(objects) and persist them for further processing. If a important object was deleted during processing the system start the processing stage from the begging using less strict generalization rules.

 Where the **OverallValidator** does validation based on number of neuronal connections to the pattern tagged with one event. The threshold value of the connection could be set as for example 20 percent per step and 60 percent per overall process (this should be clarified).



