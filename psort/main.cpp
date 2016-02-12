#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <omp.h>

#include "psort.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

/**
 * Color a string red.
 * @param str The string to color
 */
inline string makeRed(string str)
{
    return "\033[1;31m" + str + "\033[0m";
}

/**
 * Makes sure a vector is sorted correctly.
 */
template <class T>
void checkSorted(const vector<T> & data)
{
    typename vector<T>::const_iterator iter;
    for(iter = data.begin(); iter != data.end() - 1; ++iter)
    {
        if(*iter > *(iter + 1))
        {
            cout << makeRed("Parallel sort incorrect") << endl;
            return;
        }
    }
}

/**
 * Initializes a vector with random ints.
 * @param size The number of elements to fill the vector with
 */
vector<int>* getRandomVector(size_t size)
{
    srand(time(NULL));
    vector<int>* data = new vector<int>(size);
    for(size_t i = 0; i < size; ++i)
        (*data)[i] = rand();
    return data;
}

/**
 * Prints the data elements of the given vector.
 * @param data The vector to print
 */
template <class T>
void print(const vector<T> & data)
{
    typename vector<T>::iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter)
        cout << *iter << endl;
}

/**
 * Runs two sorting algorithms on identical data and compares
 *  their runtimes.
 */
int main(int argc, char* argv[])
{

   /* std::vector<string>  lala;
    lala.push_back("adf");
    lala.push_back("bsdf");
    lala.push_back("sff");
    lala.push_back("dwj");
    lala.push_back("tk");
    lala.push_back("zyj");
    vector<string> *dataC;
    dataC=&lala;
  bool mad=ParallelSort::sorted(dataC);
   
     cout<<mad<<endl;
     ParallelSort::psort(dataC);
    
     for(int i=0;i<(*dataC).size();i++){
        cout<<(*dataC)[i]<<endl;
     }

      bool mad2=ParallelSort::sorted(dataC);
cout<<mad<<endl;*/
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " numElems" << endl;
        return 1;
    }

    int numElems = atoi(argv[1]);

    // initialize a random array for both sorting methods
    vector<int>* dataA = getRandomVector(numElems);
    vector<int>* dataB = new vector<int>();
    *dataB = *dataA;

    // sort the data with parallel quicksort
    double startTime = omp_get_wtime();
    ParallelSort::psort(dataA);
    double ptime = omp_get_wtime() - startTime;
    cout << "Parallel sort: " << ptime << endl;

    // sort the data with the STL's sort
    startTime = omp_get_wtime();
    std::sort(dataB->begin(), dataB->end());
    double stime = omp_get_wtime() - startTime;
    cout << "STL sort: " << stime << endl;

    // check if the data is sorted correctly
    checkSorted(*dataA);

    // print the sorted data (if we want to)
    //print(dataA);

    delete dataA;
    delete dataB;
    return 0;
}
