gatb:
	git clone https://github.com/GATB/gatb-core.git;
	cd gatb-core/gatb-core; mkdir build ; cd build ; cmake .. ; make -j8


run:
	cd gatb-core/gatb-core/examples/; make ../../../Project/kmer3;
