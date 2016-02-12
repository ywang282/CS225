/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    length=0;
    ListNode * curr=tail;
    while (curr!=NULL) {
        tail=tail->prev;
        delete curr;
        curr=tail;
    }
    head = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    length++;
    ListNode * p;
    if(head==NULL){
        head=new ListNode(ndata);
        tail=head;
        length=1;
        
    }
    else {
        head->prev=new ListNode(ndata);
        p=head;
        head=head->prev;
        head->next=p;
        p=NULL;
    }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    length++;
    if (tail==NULL) {
        tail=new ListNode(ndata);
        head=tail;
    }
    else{
        ListNode * p=tail;
        tail->next=new ListNode(ndata);
        tail=tail->next;
        tail->prev=p;
        p=NULL;
    }
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    if(startPoint==endPoint) return;
    if(startPoint==NULL||endPoint==NULL) return;
    ListNode * b;
    ListNode * a;
    
    ListNode * c;
    ListNode * n;
    ListNode * t;
    
    b=startPoint->prev;
    a=endPoint->next;
    
    startPoint=endPoint;
    c=startPoint;
    n=c->prev;
    
    while(n!=NULL && n!=b){
        t=n->prev;
        c->next=n;
        n->prev=c;
        c=n;
        n=t;
    }
    startPoint->prev=NULL;
    endPoint=c;
    endPoint->next=NULL;
    c=NULL;
    n=NULL;
    t=NULL;
    if(b==NULL){
        head=startPoint;
    }
    else{
        b->next=startPoint;
        startPoint->prev=b;
    }
    if(a==NULL){
        tail=endPoint;
    }
    else{
        endPoint->next=a;
        a->prev=endPoint;
    }
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
        if(n>length){reverse(head,tail);}
        else if(n<=1){return;}
        else {
            int count=length/n;
            int remainder=length%n;
            ListNode * t;
            ListNode * curr;
            curr=head;
    
            while(count!=0){
                for (int i=0; i<n; i++) {
                    if(i==0) {t=curr;}
                    else {t=t->next;}
                }
                reverse(curr,t);
                curr=t->next;
                count--;
            }
            if (remainder==0) {
                return;
            }
            else {
                reverse(curr,tail);
            }
        }
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    if (head==NULL||tail==NULL||head==tail||length==0||length==1||length==2) {
        return;
    }
    else{
        ListNode * curr;
        ListNode * left;
        ListNode * right;
        
        curr=head;
        
        while (curr->next!=tail) {
            left=curr;
            curr=curr->next;
            right=curr->next;
            
            left->next=NULL;
            curr->prev=NULL;
            curr->next=NULL;
            right->prev=NULL;
            
            left->next=right;
            right->prev=left;
            
            tail->next=curr;
            curr->prev=tail;
            tail=curr;
            
            curr=right;
        }
    }
    
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();//return a new list that is NULL;

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)//point==0
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{	
	if(splitPoint==0){
		return start;	
	}
	else if(start==NULL){
		return NULL;	
	}
	else if(splitPoint==length){
		return NULL;
	}
	else{
		int count=1;
		while(count!=splitPoint){
		////////////////////////////////////////////
			start=start->next;
			count++;
		}
		ListNode * t=start;
		
		start=start->next;
		t->next=NULL;
		start->prev=NULL;
	
		return start;
	}
	
	
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
	
	if(first==NULL) return second;
	if(second==NULL) return first;
	
	ListNode * out;
	
	if((first->data)<(second->data)){	
		out=first;
		first=first->next;
	}
	else {
		out=second;
		second=second->next;
	}
	ListNode * temp=out;


	while(first!=NULL||second!=NULL){
		if(first!=NULL && second!=NULL){
			if((second->data)<(first->data)){
				out->next=second;
				second->prev=out;
				second=second->next;
				out=out->next;
			}
			else{
				out->next=first;
				first->prev=out;
				first=first->next;
				out=out->next;
			}		
		}
		if(first==NULL){
			out->next=second;
			second->prev=out;
			break;
			
		}
		if(second==NULL){
			out->next=first;
			first->prev=out;
			break;
		}
	}
	return temp;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head,length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
	if(chainLength==1) return start;
	else{	
		
		ListNode * end= split(start,chainLength/2);
		start=mergesort(start,chainLength/2);
		end=mergesort(end,chainLength-chainLength/2);
		return merge(start,end);
	}	
}
