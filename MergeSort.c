/***************************************************************
  Student Name: Mikayla Timm
  File Name: MergeSort.c adapted from Sorting project in DSA1
  Assignment number 3

 *MergeSort.c implements the functions that perform a merge sort.
***************************************************************/

#include "MergeSort.h"
#include <stdlib.h>
#include <stdio.h>

/* Merge function. Compares the numbers in the two arrays nums1 and nums2. 
 * whichever one is less is added to the current index in nums until both arrays
 * have been traversed. Also sorts the indices array corresponding to the costs.
 */
void merge(double *nums, double *nums1, double *nums2, int *indices, int *ind1, int *ind2, int count, int nums1Count, int nums2Count){
    int i = 0, j = 0, k = 0;
    while(i < nums1Count && j < nums2Count){
        if(nums1[i] <= nums2[j]){
            //nums[k++]=nums1[i++];
            nums[k] = nums1[i];
            indices[k] = ind1[i];
            i++;
        }
        else{
            //nums[k++]=nums2[j++];
            nums[k] = nums2[j];
            indices[k] = ind2[j];
            j++;
        }
        k++;
    }
    while(k < count){
        if(i == nums1Count){
            nums[k]=nums2[j];
            indices[k]=ind2[j];
            k++;
            j++;
        }
        else{ //j==nums2Count
            nums[k]=nums1[i];
            indices[k] = ind1[i];
            k++;
            i++;
        }
    }
}
/* MergeSort function is recursive. Creates 2 new subarrays each with half the 
 * number of items as the previous array size. Calls merge once it hits the smallest
 * subarray size (1), and then goes back through the function calls, merging the
 * subarrays until they are eventually sorted.
 */
void mergeSort(double *nums, int *indices, int count){
    if (count <= 1) return;
    int i, j=0;
    int nums1Count = count/2;
    int nums2Count = count - nums1Count;
    double *nums1 = (double *)malloc((nums1Count)*sizeof(double));
    //indices array must also be sorted
    int *ind1 = (int *)malloc((nums1Count)*sizeof(int));
    if(nums1==NULL || ind1==NULL){
        fprintf(stderr, "memory allocation failed");
        return;
    }
    for(i=0; i<nums1Count; i++){
        nums1[i] = nums[i];
        ind1[i] = indices[i];
    }
    double *nums2 = (double *)malloc((nums2Count)*sizeof(double));
    int *ind2 = (int *)malloc((nums2Count)*sizeof(int));
    if(nums2==NULL || ind2 == NULL){
        fprintf(stderr, "memory allocation failed");
        return;
    }
    for(; i<count; i++){
        nums2[j] = nums[i];
        ind2[j] = indices[i];
        j++;
    }
    mergeSort(nums1, ind1, nums1Count);
    mergeSort(nums2, ind2, nums2Count);
    merge(nums, nums1, nums2, indices, ind1, ind2, count, nums1Count, nums2Count);
    free(nums1);
    free(nums2);
    free(ind1);
    free(ind2);
}
