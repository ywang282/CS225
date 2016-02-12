/**
 * @file psort.h
 */

#ifndef _PSORT_H_
#define _PSORT_H_

#include <iostream>
#include <vector>
#include <omp.h>

using std::vector;

namespace ParallelSort
{
    /**
     * Public wrapper for the parallel sort implementation.
     * @param array The structure to sort
     */
    template <class T>
    void psort(vector<T>* array);

    template <class T>
    void swap(vector<T>* array,int index_one, int index_two);

    template <class T>
    int partition(vector<T>* array,int low,int hign,int pivotIndex);

    template <class T>
    void quicksort(vector<T>* array, int low, int high,int eve);


    template <class T>
    void merge(vector<T>* array, int start,int size1,int size2);

    template <class T>
    void mergeSort(vector<T>* array,int start,int size,int check);

    template <class T>
    void help(T* & from,T* & to,int start,int size1,int size2);
    
    template <class T>
    void copy(T* & from,T* & to,int start,int size);

}

#include "psort.cpp"
#endif
