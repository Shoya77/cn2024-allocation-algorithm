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

 * gen-data-cost239: This binary generates the datasets for COST 239 model using basic parameters, number of servers, number of IoT devices, each server capacity, edge delays between a device and a servers and servers.
 * gen-data-jpn25: This binary generates the datasets for JPN 25 model using basic parameters, number of servers, number of IoT devices, each server capacity, edge delays between a device and a servers and servers.
 * gen-data-kanto: This binary generates the datasets for JPN Kanto model using basic parameters, number of servers, number of IoT devices, each server capacity, edge delays between a device and a servers and servers.
 * gen-data-nsfnet: This binary generates the datasets for NSFNET model using basic parameters, number of servers, number of IoT devices, each server capacity, edge delays between a device and a servers and servers. 
 * allocator: This binary solves the server allocation problem for the IoT monitoring services in a polynomial-time computational time complexity.


To clean up the binaries use following command:

```
make clean
```
data file create at "data/jpn2514-2000-0.300000-2024030801.txt"


generate file

```
./generator models/JPN25_geo.csv models/JPN25_net.csv models/JPN25_area.csv data/jpn25 14 2000 0.3 2024030801
```

execute

```
./allocator ./data/jpn25.txt

```
