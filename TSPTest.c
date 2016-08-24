/***************************************************************
  Student Name: Mikayla Timm
  File Name: TSPTest.c
  Assignment number 3

 *TSPTest.c Runs both a brute force and genetic algorithm approach 
 * to solving the Traveling Salesman Problem. 
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BruteForce.h"
#include "Genetic.h"

#define numWeights 380
/*
 * Reads in the path weights from theCities.txt, fills them into the graph
 */
void getWeights(FILE *citiesFile);
/*
 * Prints the best path and lowest cost found for the brute force algorithm
 */
void printBest(int numCities);

int main() {
    clock_t timerBF = 0;
    clock_t timerGA = 0;
    int toursPerGen;
    int numGens;
    double percentM;
    double percentE;
    int numCities;
    FILE *presetsFile = fopen("thePresets.txt", "r"); 
    FILE *citiesFile = fopen("theCities.txt", "r"); //city weights
    //read in presets
    fscanf(presetsFile, "%d", &toursPerGen);
    fscanf(presetsFile, "%d", &numGens);
    fscanf(presetsFile, "%lf", &percentM);
    fscanf(presetsFile, "%lf", &percentE);
    fscanf(presetsFile, "%d", &numCities);
    
    getWeights(citiesFile); //put the weights in the adjacency matrix
    //initialize first tour: 12345678...numCities-1
    int i;
    for(i=0; i < numCities-1; i++){
        s[i] = i+1;
    }
    //run brute force algorithm and print results
    lowestCost = calculateCost(numCities-1);
    timerBF = clock();
    PermuteIter(numCities-1);
    timerBF = (clock() - timerBF) / (CLOCKS_PER_SEC / 1000);
    double timerB = timerBF/1000;
    printBest(numCities);
    fprintf(stderr, "Time to run BF: %.2lf secs\n\n", timerB);
    //run genetic algorithm and print results
    timerGA = clock();
    GA(toursPerGen, numGens, percentM, percentE, numCities);
    timerGA = (clock() - timerGA) / (CLOCKS_PER_SEC / 1000);
    double timerG = timerGA/1000;
    fprintf(stderr, "Time to run GA: %.2lf secs\n", timerG);
    fclose(presetsFile);
    fclose(citiesFile);
    return 0;
}
/*
 * Reads in the path weights from theCities.txt, fills them into the graph
 */
void getWeights(FILE *citiesFile){
    //read in all 380 doubles in the file
    int i;
    int j;
    for(i=0; i < maxNumCities; i++){
        for(j=0; j < maxNumCities; j++){
            if(i == j){
                weights[i][j] = 0;
            }
            else{
                fscanf(citiesFile, "%lf", &weights[i][j]);
            }
        }
    }
}
/*
 * Prints the best path and lowest cost found for the brute force algorithm
 */
void printBest(int numCities){
    fprintf(stderr, "Lowest Cost BF: %.2lf\nLowest Path BF: ", lowestCost);
    fprintf(stderr, "0 ");
    int i;
    for(i=0; i < numCities-1; i++){
        fprintf(stderr, "%d ", lowestPath[i]);
    }
    fprintf(stderr, "0\n");
} 
