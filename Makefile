CFLAGS = -g -Wall
CC = gcc

objects = BruteForce.o Genetic.o MergeSort.o TSPTest.o 

test : $(objects)
	  $(CC) -o test $(objects) 

BruteForce.o : BruteForce.c BruteForce.h
	  gcc -c -Wall BruteForce.c
Genetic.o : Genetic.c Genetic.h BruteForce.h MergeSort.h
	  gcc -c -Wall Genetic.c
MergeSort.o : MergeSort.c MergeSort.h 
	  gcc -c -Wall MergeSort.c
TSPTest.o : TSPTest.c BruteForce.h Genetic.h
	  gcc -c -Wall TSPTest.c

.PHONY : clean
clean : 
	  rm test $(objects)
