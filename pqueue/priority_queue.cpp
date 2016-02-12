#include "priority_queue.h"
#include <vector>
#include <iostream>
using namespace std;

/*creat an empty pairing heap*/
template <class T>
PriorityQueue<T>::PriorityQueue()
{
	root=NULL;
}

template <class T>
typename PriorityQueue<T>::treeNode * PriorityQueue<T>::copy(typename PriorityQueue<T>::treeNode * & node)
{	
	if(node==NULL){
		return NULL;
	}
	treeNode * newNode=new treeNode(node->element);
	newNode->child=copy(node->child);
	if(newNode->child!=NULL){
		newNode->child->previous=newNode;
	}
	newNode->next=copy(node->next);
	if(newNode->next!=NULL){
		newNode->next->previous=newNode;
	}
	return newNode;
}

template <class T>
PriorityQueue<T>::PriorityQueue(PriorityQueue<T>  & other)
{	
	
	root=copy(other.root);

}



template <class T>
void PriorityQueue<T>::clear(treeNode * node)
{	
	if(node==NULL){
		return;
	}
	clear(node->child);
	clear(node->next);
	delete node;
	// node->child=NULL;
	// node->next=NULL;
	// node->previous=NULL;
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{	
	clear(root);
    root==NULL;
}


/*void PriorityQueue<T>::operator=(const PriorityQueue<T> & source){
    if (this != &source){
		clear(root);
		root=NULL;
		root=copy(source.root);
	}
	return *this;
}*/

template <class T>
void PriorityQueue<T>::insert(const T & value)
{
	if(isEmpty()){
		root=new treeNode(value);
	}
	else{
		treeNode * newTreeNode=new treeNode(value);
		root=merge(root,newTreeNode);
	}
}

template <class T>
typename PriorityQueue<T>::treeNode * PriorityQueue<T>::merge(treeNode *& first,treeNode *& second){
	treeNode * out;
	if(first->element>second->element){//first is the root;
			treeNode * holder=first->child;
			first->child=second;
			second->previous=first;
			second->next=holder;
			if(holder!=NULL){
				holder->previous=second;
			}
			out=first;
			return out;
	}
	else{
		treeNode * holder=second->child;
			second->child=first;
			first->previous=second;
			first->next=holder;
			if(holder!=NULL){
				holder->previous=first;
			}
			out=second;
			return out;
	}
}

template <class T>
std::vector<typename PriorityQueue<T>::treeNode *>  PriorityQueue<T>::firstRoundMerge(std::vector<treeNode *> & v){
	int i;
	std::vector<treeNode * > grandChildren;
	for(i=0;i<(int)v.size()&&(i+1)<(int)v.size();i+=2){
		treeNode * first=v[i];
		treeNode * second=v[i+1];
		//cout<<v[1]->element<<endl;
		//cout<<v[0]->element<<endl;
		treeNode * mother=merge(first,second);
		grandChildren.push_back(mother);
		
	}

	//cout<<grandChildren.size()<<endl;
	if(i==(int)v.size()){

	}
	if(i==(int)v.size()-1){
		treeNode * temp=grandChildren[grandChildren.size()-1];
		treeNode * toMerge=v[v.size()-1];
		grandChildren.pop_back();//////will it hurt
		treeNode * mother=merge(temp,toMerge);
		grandChildren.push_back(mother);
	}

	/*for(int i=0;i<(int)v.size();i++){
		v.pop_back();
	}*/

	return grandChildren;

}

template <class T>
typename PriorityQueue<T>::treeNode * PriorityQueue<T>::secondRoundMerge(std::vector<typename PriorityQueue<T>::treeNode *> & v, treeNode *& node,int size){
	if(size==0){
		//cout<<"im here"<<endl;
		return node;
	}
	else{
		
		treeNode * tomerge=v[size-1];
	treeNode * out=merge(tomerge,node);
	return secondRoundMerge(v,out,size-1);
	}
	
}


template <class T>
typename PriorityQueue<T>::treeNode * PriorityQueue<T>::rearrange(treeNode *& node){
	if(node->next==NULL){
		return node;
	}
	std::vector<treeNode * > children;
	std::vector<treeNode * > grandChildren;//////
	treeNode * iterator=node;
	while(iterator!=NULL){
		children.push_back(iterator);
		iterator=iterator->next;
		if(iterator!=NULL){
			iterator->previous->next=NULL;
			iterator->previous=NULL;
		}

	}

	grandChildren=firstRoundMerge(children);

	//cout<<grandChildren[0]->element<<endl;

	treeNode *& toSecond=grandChildren[grandChildren.size()-1];
	//cout<<"the size is "<<grandChildren.size()-1<<endl;

	
	
	return secondRoundMerge(grandChildren,toSecond,grandChildren.size()-1);
	/*for (int i = 0; i < grandChildren.size(); ++i)
	{
		grandChildren.pop_back();
	}*/
	//return out;
}


template <class T>
T PriorityQueue<T>::pop()
{	
	if(isEmpty()){
		return T();
	}
	else{
		treeNode * out=root;
		T outElem=out->element;
		if(root->child==NULL){
			delete root;
			root=NULL;
			out=NULL;
		}
		else{
			treeNode * holder=root->child;
			root->child->previous=NULL;
			delete out;
			out=NULL;
			root=rearrange(holder);
		}
		return outElem;
	}
	
    
}

template <class T>
const T & PriorityQueue<T>::top() const
{	
	if(isEmpty()){
		return T();
	}
    else{
    	return root->element;
    }
}

template <class T>
bool PriorityQueue<T>::isEmpty() const
{
    return root==NULL;
}


