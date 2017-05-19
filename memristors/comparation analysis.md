Software name     | Simulation engine |Visual editor     | Procs|Cons|Total
:--------:|:------:|:---------:|:-------:|:-:|:-:|
SPICE | SPICE|no |allows to create large text schemas to simulate|suprising lack of<br> basic documentation|Basic engine for<br> everything
NGSPICE | SPICE|no|allows to create large text schemas to simulate|not updated for long<br>uses old libraries to compile|Some advanced wrapping<br> around SPICE
KiCad EDA     | ngspice|yes||pretty difficult to launch simulation<br>not big component library<br>not open source|shematic editor with ngspice launcher
LTspice|upgraded SPICE|yes|Some memristor simulations exists([GitHub](https://github.com/knowm/memristor-models-4-all))|not open source<br>but free to use|

In general: largest chunk of simulators uses SPICE or NGSPICE engines for simulation. So no reason to use other simulators without graphical editor. Those engines allow to create schematics with big amount of components. They're not updated for long, so e.g. some NGSPICE sub components does not compile. On the other hand most of graphical schematic editors just translate graphical to text and fed it to spices. So, choise is based just on comfort of using and accessebility to additional components, especially memrisotrs. Result is LTSPICE.

Software Name | Engine(s) | Development | Memristors | Custom components | Comments | Conclusion
:-:|:-:|:-:|:-:|:-:|:-:|:-:
KTechLab | unknown | stoped in 2009 | not implemented | no | too simple, too old | not recommended
Oregano | GnuGap, NgSpice | stoped in 2006 | not implemented | no | a lot of realistic components | not recommended
QUCS | Qucsator, NgSpice (the extension is required) | ongoing | not implemented | yes | there are memristor spice sub-schemas | recommended 

So in the last list QUCS is the only convinient tool for our research. 
