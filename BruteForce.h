/***************************************************************
  Student Name: Mikayla Timm
  File Name: BruteForce.h
  Assignment number 3

 *BruteForce.h outlines all of the functions for the brute force algorithm.
***************************************************************/

#ifndef BRUTEFORCE_H
#define	BRUTEFORCE_H

#define maxNumCities 20

//globals
double lowestCost; //if cost < min min=cost
int s[maxNumCities]; //path array 
int lowestPath[maxNumCities];
double weights[maxNumCities][maxNumCities];

/*
 * Main function called for performing the BF approach. 
 * Computes the number of permutations we need and calls perm1.
 */
void PermuteIter(int numCPermute);
/*
 * Perm1 function goes through every possible permutation, or every possible
 * path. Saves the optimal path and cost.
 */
void perm1(int, long long unsigned int);
/*
 * Swaps the two items located at index m and k.
 */
void swap(int m, int k);
/*
 * Prints the current path array with leading and ending 0's. 
 */
void printS(int n);
/*
 * Calculates the cost of the current path by adding up the weights between the 
 * cities in the path.
 */
double calculateCost(int n);

#endif	/* BRUTEFORCE_H */