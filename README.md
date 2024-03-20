# cn2024-allocation-algorithm

This repository has all the files needed to compile the code used in the paper "Polynomial-Time Server Allocation Algorithm in Delay-Sensitive Internet-of-Things Monitoring Services".

The following content comes with this code:

 * README.md: This file with code description
 * Makefile: Used to compile the binaries necessary for executing the algorithm
 * Data_Create_COST239.cpp:　Used to create an input dataset based on the COST239 network model
 * Data_Create_JPN25.cpp: Used to create an input dataset based on the JPN25 network model
 * Data_Create_Kanto.cpp: Used to create an input dataset based on the JPN Kanto region network model
 * Data_Create_NSFNET.cpp: Used to create an input dataset based on the NSFNET network model
 * poly_algo_allocator.cpp: Main program to solve the server allocation problem in IoT monitoring services

# How to use

You need to use a C++ environment with standard libraries to compile the code. With
that, to compile, use the following command: 

```
make
```

The binaries for generating topologies and running the algorithm will generated:

 * generator: This binary generates the datasets according to each network model information given as input csv file using basic parameters, number of servers, number of IoT devices, a ratio of number of IoT devices to the total server capacities.
 * allocator: This binary solves the server allocation problem for the IoT monitoring services in a polynomial-time computational time complexity.

To clean up the binaries use following command:

```
make clean
```

The way of executing binaries, generator and allocator, is as follows:

* generator (generate dataset file)

  An argument "models/JPN25_geo.csv" contains server location information according to the JPN25 network model.
  "models/JPN25_net.csv" contains server-server distace information that is predifined based on the JPN25 network model.
  "models/JPN25_area.csv" contains information on the divided areas (the ratio of number of devices, latitude and longitude information) where IoT devices are distributed.
  "data/jpn25" is output file information for generated dataset.
  Note that you should make a directory named as "data" before you run the following code.

```
./generator models/JPN25_geo.csv models/JPN25_net.csv models/JPN25_area.csv data/jpn25 14 2000 0.3 2024030801
```

If a dataset file can be correctly generated, 
"data file create at "data/jpn2514-2000-0.300000-2024030801.txt" is output.

* allocator (solve the server allocation problem in IoT monitoring services)

  The second argument "./data/jpn25.txt" is a dataset file given as input for solving the server allocation problem.

```
./allocator ./data/jpn25.txt
```
