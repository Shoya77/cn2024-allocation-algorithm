COMPILER=g++

all: generator algorithm

generator-old: Data_Create_COST239.cpp Data_Create_JPN25.cpp Data_Create_Kanto.cpp Data_Create_NSFNET.cpp
	$(COMPILER) -o gen-data-cost239 Data_Create_COST239.cpp
	$(COMPILER) -o gen-data-jpn25 Data_Create_JPN25.cpp
	$(COMPILER) -o gen-data-kanto Data_Create_Kanto.cpp
	$(COMPILER) -o gen-data-nsfnet Data_Create_NSFNET.cpp

generator: topo-generator.cpp
	$(COMPILER) -o generator topo-generator.cpp

algorithm:
	$(COMPILER) -o allocator poly_algo_allocator.cpp

clean:
	$(RM) gen-data-cost239 gen-data-jpn25 gen-data-kanto gen-data-nsfnet allocator
