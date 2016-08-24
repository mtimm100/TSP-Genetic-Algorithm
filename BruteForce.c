/***************************************************************
  Student Name: Mikayla Timm
  File Name: BruteForce.c
  Assignment number 3
Genetic
 *BruteForce.c implements all the functions that deal with the brute force algorithm for
 * solving the Traveling salesman problem. 
***************************************************************/
#include "BruteForce.h"
#include <stdio.h>
#include <stdlib.h>
/*
 * Main function called for performing the BF approach. 
 * Computes the number of permutations we need and calls perm1.
 */
void PermuteIter(int numCPermute){
    int i;
    int n;
    long long unsigned int nfact = 1;//factorial of numCPermute
    n = numCPermute; //number of cities to permute = numcities -1
    for(i=1; i <=n; i++){
        nfact *= i;
    }
    perm1(n, nfact);
    //printf("\n");
}
/*
 * Perm1 function goes through every possible permutation, or every possible
 * path. Saves the optimal path and cost.
 */
void perm1(int n, long long unsigned int nfact){
    int m, k, p, q;
    double cost;
    long long unsigned int i;
    //printS(n);
    
    for(i = 1; i < nfact; i++){
        m = n-2;
        while(s[m]>s[m+1]){
            m = m-1;
        }
        k = n-1;
        while(s[m]>s[k]){
            k = k-1;
        }
        swap(m,k);
        p =m+1;
        q = n-1;
        while(p<q){
            swap(p,q);
            p++;
            q--;
        }
        //calculate cost
        cost = calculateCost(n);
        if(cost < lowestCost){
            int ctr;
            lowestCost = cost;
            for(ctr=0; ctr < n; ctr++){
                lowestPath[ctr] = s[ctr];
            }
        }
    }
}
/*
 * Swaps the two items located at index m and k.
 */
void swap(int m, int k){
    int tempK = s[k];
    s[k] = s[m];
    s[m] = tempK;
}
/*
 * Prints the current path array with leading and ending 0's. 
 */
void printS(int n){
    //print current path array with 0 in front and 0 at the end
    int i;
    fprintf(stderr, "0");
    for(i=0; i < n; i++){
        fprintf(stderr, "%d", s[i]);
    }
    fprintf(stderr, "0\n");
}
/*
 * Calculates the cost of the current path by adding up the weights between the 
 * cities in the path.
 */
double calculateCost(int n){
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

