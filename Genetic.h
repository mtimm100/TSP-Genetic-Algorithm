/***************************************************************
  Student Name: Mikayla Timm
  File Name: Genetic.h
  Assignment number 3

 *Genetic.h outlines all the functions implemented in Genetic.c. All the functions in
 * here deal with the genetic algorithm operations.
***************************************************************/

#ifndef GENETIC_H
#define	GENETIC_H

#include "BruteForce.h"
#include "MergeSort.h"
#include <stdlib.h>

//global structures for the algorithm
int **currentGen; //numtours x numcities-1lowestCost
int toursPerGen;
int numElites;
int numMutations;
double *costs;
double *sortedCosts;
int *sortedIndices;
int *lowestPathGA[maxNumCities];

/*
 * Takes in the presets and performs the genetic algorithm operations.
 * Finds the optimal cost and path.
 */
void GA(int toursPerGen, int numGens, double percentM, double percentE, int numCities);
/*
 * Shuffles the cities in the array to diversify the generations.
 */
void shuffle(int *path, int size);
/*
 * Calculates the cost of the tour specified by the array s. Returns the cost 
 * as a double.
 */
double calcCostGA(int n, int *s);
/*
 * Mutation function. Gets 2 indices: one random from the first half of s array,
 * one random from the second half, and swaps them.
 */
void mutate2(int n, int *s);
/*
 * Create the new generation of tours. Performs the preservation of elites,
 * mutations, and shuffling of the remaining tours. Sorts the costs.
 */
void newGen(int n);

#endif	/* GENETIC_H */

