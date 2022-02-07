# Intelligent PID Controller Tuning

## Overview

This software contains header and source that implements genetic algorithm suitable for tuning of the PID controller.
The user has to implement own fitness function as it has been implemented in the test (main.c) file.

The algorithm does not perform dynamic allocation of memory. The algorithm is not optimized.
By decreasing number of iterations and samples, execution time can be decreased dramatically.

Test solves linearized model of a DC motor. Results can also be tested in the Simulink.

