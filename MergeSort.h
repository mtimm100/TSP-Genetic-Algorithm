/***************************************************************
  Student Name: Mikayla Timm
  File Name: MergeSort.h adapted from Sorting Project from DSA1
  Assignment number 3

 *MergeSort.h outlines the functions used in performing a merge sort.
***************************************************************/
#ifndef MERGESORT_H
#define	MERGESORT_H

/* MergeSort function is recursive. Creates 2 new subarrays each with half the 
 * number of items as the previous array size. Calls merge once it hits the smallest
 * subarray size (1), and then goes back through the function calls, merging the
 * subarrays until they are eventually sorted.
 */
void mergeSort(double *, int *, int);
/* Merge function. Compares the numbers in the two arrays nums1 and nums2. 
 * whichever one is less is added to the current index in nums until both arrays
 * have been traversed. Also sorts the indices array corresponding to the costs.
 */
void merge(double *, double *, double *, int *, int *, int *, int, int, int);

#endif	/* MERGESORT_H */

