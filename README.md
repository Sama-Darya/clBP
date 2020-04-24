# clBP: closed-loop Back-propagarion
 This is a learning platform that allows for flexible and innovative learning rules in the context of closed-loop deep learning. It can be used with the conventional back-propagation or the newly developed 'local propagation of closed-loop error' algorithm. This repository is intended for use as an external library to any learning applications. 

## Building ClBP
clBP uses cmake. just enter the clBP directory from the root and type:
- ``mkdir build && cd build``
- ``cmake ..``
- ``make``
- record the path to both the generated library file (``libclBP.a``) and of the ``include`` directory for external use in other projects.