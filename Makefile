gatb:
	git clone https://github.com/GATB/gatb-core.git;
	cd gatb-core/gatb-core; mkdir build ; cd build ; cmake .. ; make -j8

main:
	cd gatb-core/gatb-core/examples/; make ../../../Project/main;

run_main:
	./Project/main -in Project/Data/FLT3.fa  -kmer-size 6 -sequences Project/Data/Sequences.fa;

clean:
	rm -f Project/main
	rm -f Project/Results/Transformation.txt

all:
	make clean
	make main
	make run_main
