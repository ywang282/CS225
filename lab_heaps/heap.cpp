/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <iostream>

 using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx ) const {
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx ) const {
    if(currentIdx*2<=_elems.size()-1){
        return true;
    }
    else{
        return false;
    }
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    if(rightChild(currentIdx)<=_elems.size()-1){//has two child
        T left=_elems[leftChild(currentIdx)];
        T right=_elems[rightChild(currentIdx)];
        if(higherPriority(left,right)){
            return leftChild(currentIdx);
        }
        else{
            return rightChild(currentIdx);
        }
    }
    else{
        return leftChild(currentIdx);
    }
    
    
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
    if(!hasAChild(currentIdx)){
        return;
    }
    else{
        size_t target=maxPriorityChild(currentIdx);
        if(higherPriority(_elems[target],_elems[currentIdx])){
            std::swap(_elems[currentIdx],_elems[target]);
            heapifyDown(target);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    _elems.push_back(T());//yay now size is 1;
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    _elems.push_back(T());
    for(size_t i=0;i<elems.size();i++){
        _elems.push_back(elems[i]);
    }
   for(size_t j=_elems.size()-1;j>0;j--){
        heapifyDown(j);
   }
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    if(!empty()){
        T out=_elems[1];
        _elems[1]=_elems[_elems.size()-1];
        _elems.pop_back();
        heapifyDown(1);
        return out;
    }
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    if(!empty()){
        return _elems[1];
    }
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
   return _elems.size()<=1;
}


