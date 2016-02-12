/**
 * @file priority_queue.h
 */

#ifndef _PQUEUE_H_
#define _PQUEUE_H_
#include <vector>

/**
 * Implements the max priority queue ADT.
 *
 * The implementation is up to you, but you must complete all the given
 *  public functions. You will need to add some member variables and private
 *  helper functions.
 */
template <class T>
class PriorityQueue
{
    public:
        /**
         * Constructor: creates an empty priority queue.
         */
        PriorityQueue();

        ~PriorityQueue();

        PriorityQueue(PriorityQueue<T>  & other);

        //void operator=(const PriorityQueue<T> & source);

        /**
         * Inserts the given value into the queue.
         *
         * @param value The value to be inserted.
         */
        void insert(const T & value);

        /**
         * Removes the highest value (and its associated data) from the
         *  queue.
         *
         * @return A copy of the removed (maximum) element
         */
        T pop();

        /**
         * Returns the highest value from the queue. Does NOT remove it.
         *
         * @return A copy of the maximum element
         */
        const T & top() const;

        /**
         * Determines if the queue is empty. Should be O(1).
         *
         * @return A boolean value indicating whether the queue is
         *  empty.
         */
        bool isEmpty() const;


    private:


        class treeNode{
            public:
                T element;
                treeNode * previous;
                treeNode * next;
                treeNode * child;
                treeNode(){
                    element=T();
                    previous=NULL;
                    next=NULL;
                    child=NULL;
                }

                treeNode(const T & value){
                    element=value;
                    previous=NULL;
                    next=NULL;
                    child=NULL;
                }
            private:
        };


        treeNode * root;

        void clear(treeNode * node);

        treeNode * copy(treeNode * & node);

        treeNode * merge(treeNode *& first,treeNode *& second);

        treeNode * rearrange(treeNode *& node);

        std::vector<treeNode *>  firstRoundMerge(std::vector<treeNode *> & v);

       treeNode * secondRoundMerge(std::vector<treeNode *> & v, treeNode *& node,int size);

       



};

#include "priority_queue.cpp"
#endif
