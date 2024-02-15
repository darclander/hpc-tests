CC=g++
OPTIMIZATION= #-O3
CFLAGS=

.PHONY: all openmp

openmp: ./src/openmp.cpp
	$(CC) $< -o ./debug/$@ -fopenmp
	
all: openmp

clean: 
	rm ./debug/*