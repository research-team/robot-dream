# Direct translation file format

[Neuralynx formats description](http://neuralynx.com/software/NeuralynxDataFileFormats.pdf)

We will use continuously sampled channel (CSC) format. File extension for this format
is ".ncs".

We will use fixed number of data points per record namely 512. Thus payload is always
512 16-bit integers.


## Neural coding

To encode *on/off* signals (such as touch or wall hit sensor) we map each channel to separate sensory neuron and fire a single spike whenever the sensor goes *on*.

To encode *continuous values* (such as distance or brightness) we employ [rate coding](https://en.wikipedia.org/wiki/Neural_coding#Rate_coding). Rational for this is simplicity of the coding scheme on one hand and on the other hand the fact that (currently) we map input signals to sensory-motor cortex, and muscular system is known to use rate coding.
