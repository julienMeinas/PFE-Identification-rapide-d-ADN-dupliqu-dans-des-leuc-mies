
gatb:
	git clone https://github.com/GATB/gatb-core.git;
	cd gatb-core/gatb-core; mkdir build ; cd build ; cmake .. ; make -j8

# change this to the folder where gatb-core is
GATB=$(shell pwd)/gatb-core/gatb-core/
GATB_LIB=$(GATB)/build/lib
CXXFLAGS =  -std=c++0x -O3  -I$(GATB)/src  -I$(GATB)/build/include -I$(GATB)/thirdparty
LDFLAGS=   -L$(GATB_LIB) -lgatbcore  -lpthread -lhdf5 -lz -std=c++0x -ldl -static
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%,$(SRCS))


clean:
	rm -rf Project/main
	rm -rf Project/Results/*

%: %.cpp
	$(CXX) $(CXXFLAGS) $^ Project/Class/Filter/ClassFilter.cpp Project/Class/Cleaning/ClassCleaning.cpp Project/Class/Breakpoint/ClassBreakpoint.cpp Project/Class/Breakpoint/BreakPoint.cpp -o $@  $(LDFLAGS)

run_main:
	./Project/main -in Project/Data/FLT3.fa -kmer-size 15 -sequences Project/Data/P8-L1810648D09.fastq.gz