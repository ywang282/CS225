

/**
 * @file psort.cpp
 */

/**
 * Public wrapper for the parallel sort implementation.
 * @param array The structure to sort
 */
 #include <iostream>
 #include <cmath>
 #include <omp.h>
 using namespace std;



template <class T>
void ParallelSort::copy(T* & from,T* & to,int start,int size)
{
    
    omp_set_num_threads(5);
    #pragma omp parallel 
    {
        #pragma omp for
        for(int i=0;i<size;i++)
        {
            to[start+i]=from[start+i];
        }
    }

}









template <class T>
void ParallelSort::help(T* & from,T* & to,int start,int size1,int size2)
{
    
    int start1=start;
    int start2=start+size1;
    int start1End=start+size1;
    int start2End=start+size1+size2;

    int write=start;
    int writeEnd=start+size1+size2;
    // omp_set_num_threads(4);


    for(;write != writeEnd;)
    {
        if(start1==start1End)
        {
            to[write]=from[start2];
            write++;
            start2++;           
        }

        else if(start2==start2End)
        {
            to[write]=from[start1];
            write++;
            start1++;           
        }


        else
        {

            if(from[start1]<from[start2])
            {
                to[write]=from[start1];
                write++;
                start1++;
            }
            else if(from[start1]>from[start2])
            {
                to[write]=from[start2];
                write++;
                start2++;
            }
            else
            {
                to[write]=from[start1];
                write++;
                start1++;
            }

        }

    }


}

template <class T>
void ParallelSort::quicksort(vector<T>* array, int low, int high,int eve){



    if(high>low){
    int Index=(low+high)/2;
    int pivotIndex=partition(array, low,high,Index);
    if(eve !=0){
        #pragma omp task
        quicksort(array, low, pivotIndex - 1,eve-1);
        quicksort(array, pivotIndex+1, high,eve-1);
    }else{
        
        quicksort(array, low, pivotIndex - 1,0);
        quicksort(array, pivotIndex+1, high,0);
    }
    
   
}

}
template <class T>
int ParallelSort::partition(vector<T>* array,int low,int high,int pivotIndex){
 T pivotValue=(*array)[pivotIndex];
    swap( array, pivotIndex, high);
    int storeIndex=low;
    for(int i=low ; i<high ; i++)
    {
        if((*array)[i]< pivotValue)
        {
            swap( array, storeIndex, i);
            storeIndex++;
        } 
    }
    swap( array, high, storeIndex);
    return storeIndex;

}


template <class T>
void ParallelSort::swap(vector<T>* array,int index_one, int index_two){

T temp     =(*array)[index_one];
    (*array)[index_one]=(*array)[index_two];
    (*array)[index_two]=temp;

}





template <class T>
void ParallelSort::psort(vector<T>* array)
{
    
    if((*array).size()>2100000){
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                quicksort(array, 0, (*array).size()-1,20);
            }
        }
        
    }
    else{
    int arraySize= (int)(  (*array).size()  );
    T* from=new T[arraySize];
    T* to=new T[arraySize];

    //copy data to from
    for(int i=0;i<arraySize;i++)
    {
        from[i]=(*array)[i];
    }



    
    int size=1;
    int startPoint=0;
    T* temp;    

    for( ;size < arraySize ; size=size*2)
    {


        startPoint=0;
        int threadNum=arraySize/(2*size);


// omp_set_num_threads(3);
#pragma omp task 
{
    #pragma omp for nowait
    for(int i=0;  i<threadNum ;  i++)
    {                               
        help(from,to,2*i*size,size,size);               
                                    
    }
}
                            
                    
     


        startPoint = (size+size)*threadNum;
        if(arraySize - startPoint > size )
        {
            help(from,to,startPoint,size,arraySize - startPoint - size);
        }       
        else 
        {
            copy(from,to,startPoint,arraySize - startPoint);
        }



        
        temp=from;
        from=to;
        to=temp;

    }
        

    



// omp_set_num_threads(5);
    #pragma omp task 
    {
        // #pragma omp for
        for(int i=0;i<arraySize;i++)
        {
            (*array)[i]=from[i];
        }
    }
    


    delete [] from;
    delete [] to;
}
}







