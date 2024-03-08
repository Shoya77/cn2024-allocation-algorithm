# cn2024-allocation-algorithm

This repository has all the files needed to compile the code used in the paper "Polynomial-Time Server Allocation Algorithm in Delay-Sensitive Internet-of-Things Monitoring Services".

The following content comes with this code:

 * README.md: This file with code description
 * Makefile: Used to compile the binaries necessary for executing the algorithm
 * Data_Create_COST239.cpp:
 * Data_Create_JPN25.cpp:
 * Data_Create_Kanto.cpp:
 * Data_Create_NSFNET.cpp:
 * poly_algo_allocator.cpp:

# How to use

You need to use a C++ environment with standard libraries to compile the code. With
that, to compile, use the following command:

```
make
```

The binaries for generating topologies and running the algorithm will generated:

 * gen-data-cost239:
 * gen-data-jpn25:
 * gen-data-kanto:
 * gen-data-nsfnet:
 * allocator:


To clean up the binaries use following command:

```
make clean
```
