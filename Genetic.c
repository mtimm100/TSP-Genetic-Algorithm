/***************************************************************
  Student Name: Mikayla Timm
  File Name: Genetic.c
  Assignment number 3

 *Genetic.c contains all of the operations for the genetic algorithm approach
 * for solving the Traveling Salesman Problem. 
***************************************************************/
#include "BruteForce.h"
#include "MergeSort.h"
#include "Genetic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Takes in the presets and performs the genetic algorithm operations.
 * Finds the optimal cost and path.
 */
void GA(int TPG, int numGens, double percentM, double percentE, int numCities){
    //srand(time(NULL));
    numElites = (int)(percentE*(double)TPG);
    numMutations = (int)(percentM*(double)TPG);
    toursPerGen = TPG;
    int n = numCities-1;
    int i;
    int j;
    //malloc the currentGen array //toursPerGen x numCities-1
    currentGen = (int **)malloc(sizeof(int *)*toursPerGen); 
    for(i = 0; i < toursPerGen; i++){
        currentGen[i] = (int *)malloc(sizeof(int)*n);
    }
    costs = (double *)malloc(sizeof(double)*toursPerGen);
    sortedCosts  = (double *)malloc(sizeof(double)*toursPerGen);
    sortedIndices = (int *)malloc(sizeof(int)*toursPerGen);
    
    //start by loading 1234567 into all tours in the currentGen matrix
    for(i=0; i < toursPerGen; i++){
        for(j=0; j<n; j++){
            currentGen[i][j] = j+1;
        }
    }
    
    //shuffle all of them
    for(i=0; i < toursPerGen; i++){
        shuffle(currentGen[i], n);
    }
    //get the costs, put each one into the cost array. first tour's cost at index 0, etc
    for(i=0; i<toursPerGen; i++){
        costs[i] = calcCostGA(n,currentGen[i]);
        sortedCosts[i] = costs[i]; //save the costs to sortedCosts for sorting
    }
    //sort the costs and indices. initialize indices to 0 1 2 3... toursPerGen-1
    for(i=0; i < toursPerGen; i++){
        sortedIndices[i] = i;
    }
    mergeSort(sortedCosts, sortedIndices, toursPerGen);
    //lowestCostGA = sortedCosts[0];
    //new generations
    for(i=0; i < numGens; i++){
        newGen(n);
    }
    
    //print results
    fprintf(stderr, "Lowest Cost GA: %.2lf\n", sortedCosts[0]);
    fprintf(stderr, "Lowest Path GA: ");
    fprintf(stderr, "0 ");
    for(i=0; i < numCities-1; i++){
        fprintf(stderr, "%d ", currentGen[sortedIndices[0]][i]);
    }
    fprintf(stderr, "0\n");
    double percentOfOptimal = (sortedCosts[0]/lowestCost)*100;
    fprintf(stderr, "Percent of optimal: %.2lf\n", percentOfOptimal);
    free(costs);
    free(sortedCosts);
    free(sortedIndices);
    free(currentGen);
}
/*
 * Shuffles the cities in the array to diversify the generations.
 */
void shuffle(int *path, int size){
    if (size > 1) 
    {
        int i;
        for (i = 0; i < size - 1; i++) 
        {
          int j = i + rand() / (RAND_MAX / (size - i) + 1);
          int t = path[j];
          path[j] = path[i];
          path[i] = t;
        }
    }
}

/*
 * Calculates the cost of the tour specified by the array s. Returns the cost 
 * as a double.
 */
double calcCostGA(int n, int *s){
    int i;
    double cost = 0;
    for(i=0; i < n-1; i++){
        cost+=weights[s[i]][s[i+1]]; //add up the costs for the path found in permutation
    }
    //add in the cost for the last city to 0 
    cost += weights[s[n-1]][0];
    //add in the cost for 0 to the first city in the permutation
    cost += weights[0][s[0]];
    return cost;
}
/*
void mutate1(int n, int *s){
    //take a random number between 0 to n/2 and a random number 
    int ind1;
    int ind2;
    int ind3;
    int diff;
    diff = (n-1);
    do{
        ind3 = (int)(((double)(diff+1)/RAND_MAX) * rand() + 0);
        ind1 = (int)(((double)(diff+1)/RAND_MAX) * rand() + 0);
        ind2 = (int)(((double)(diff+1)/RAND_MAX) * rand() + 0);
    }while(ind1 == ind2 || ind2 == ind3 || ind1 == ind3); //find 3 different indices
    //swap those 3 indices.
    int temp1 = s[ind1];
    s[ind1] = s[ind2];
    s[ind2] = s[ind3];
    s[ind3] = temp1;
    
}*/
/*
 * Mutation function. Gets 2 indices: one random from the first half of s array,
 * one random from the second half, and swaps them.
 */
void mutate2(int n, int *s){
    int ind1; 
    int ind2;
    int diff;
    //get random index from first half of the array
    diff = (n/2) -0;
    ind1 = (int)(((double)(diff+1)/RAND_MAX) * rand() + 0);
    //get random index from second half of the array
    diff = (n-1) - (n/2);
    ind2 = (int)(((double)(diff+1)/RAND_MAX) * rand() + (n/2));
    //swap the two
    int temp1 = s[ind1];
    s[ind1] = s[ind2];
    s[ind2] = temp1;
}
/*
 * Create the new generation of tours. Performs the preservation of elites,
 * mutations, and shuffling of the remaining tours. Sorts the costs.
 */
void newGen(int n){
    int i;
    //create new generation
    //don't mess with 0-> numElites-1 
    //mutate the paths indexed at numElites -> numMutations+numElites
    int mutateStart = numElites;
    int mutateEnd = numElites+numMutations;
    for(i=mutateStart; i < mutateEnd; i++){
        mutate2(n, currentGen[sortedIndices[i]]);
    }
    //shuffle the rest (numMutations+numElites -> toursPerGen)
    for(i=mutateEnd; i < toursPerGen; i++){
        shuffle(currentGen[sortedIndices[i]], n);
    }
    //get the costs of the newly generated generation
    for(i=0; i<toursPerGen; i++){
        costs[i] = calcCostGA(n,currentGen[i]);
        sortedCosts[i] = costs[i]; //save the costs to sortedCosts for sorting
    }
    //sort the costs and indices. initialize indices to 0 1 2 3... toursPerGen-1
    for(i=0; i < toursPerGen; i++){
        sortedIndices[i] = i;
    }
    mergeSort(sortedCosts, sortedIndices, toursPerGen);
}

    