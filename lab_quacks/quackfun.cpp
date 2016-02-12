/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T QuackFun::sum(stack<T> & s)
{
    if(s.empty()){//base case. return the default value;
        return T();
    }
    
    T top=s.top();//a temp variable of type T that hold the value of the top value;
    s.pop();
    T out=top+sum(s);	// the return value
    s.push(top);//fix the changed stack;
    return out;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void QuackFun::scramble(queue<T> & q)
{
    
    queue<T> q2;
    int count=1;
    while((int)q.size()>count){
        
        for(int i=0;i<count;i++){
            q2.push(q.front());
            q.pop();
        }
        count++;//copy the first round
        
        
        if((int)q.size()>=count && (int)q.size()>0){//reverse the second round
            stack<T> s;
            for(int i=0;i<count;i++){
                
                s.push(q.front());
                q.pop();
            }
            
            for(int i=0;i<count;i++){
                q2.push(s.top());
                s.pop();
            }
            count++;
        }
        else if((int)q.size()<count && (int)q.size()>0){//if the size is not big enough. then do partial reverse
            stack<T> s;
            int length=(int)q.size();
            for(int i=0;i<length;i++){
                s.push(q.front());
                q.pop();
            }
            
            for(int i=0;i<length;i++){
                q2.push(s.top());
                s.pop();
            }
        
        }
    }
    
    if((int)q.size()==0){
        int l=(int)q2.size();
        for(int i=0;i<l;i++){
            q.push(q2.front());
            q2.pop();
        }
    }
    
    else{
        int length=(int)q.size();
        for(int i=0;i<length;i++){//first round size not big enough
            q2.push(q.front());
            q.pop();
        }
        int l=(int)q2.size();
        for(int i=0;i<l;i++){
           q.push(q2.front());
            q2.pop();
        }
    }
}

/**
 * @return true if the parameter stack and queue contain only elements of exactly
 *  the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in your return statement,
 *      and you may only declare TWO local variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be sure to comment your code VERY well.
 */
template <typename T>
bool QuackFun::verifySame(stack<T> & s, queue<T> & q)
{	
	/*bool out=true;
	if(s.size()==0 && q.size()==0){//base base. when the size is equal , that means they are the same;
		return true;;
	}
	
	
	T tops=s.top();
	T backq=q.back();
	
	
	if(tops==backq){
		s.pop();
		for(int i=0;i<q.size()-1;i++){//used a for loop. not sure how to do without a forloop
			q.push(q.front());
			q.pop();
		}
		q.pop();
		out=verifySame(s,q);//keep the result;
		s.push(tops);
		q.push(backq);
	}
	
	
	else {
		out= false;
	}
	
	return out;*/
	
	
	//out=true
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	bool out=true;
	if(s.empty()){
		return true;
	}
	
	T tops=s.top();
	s.pop();
	
	
	out=verifySame(s,q);
	
	
	if(out==true)
	{
		if(tops==q.front()){
			out=true;
		}
		else {
			out=false;
		}
	}
	s.push(tops);
	T topq=q.front();
	q.pop();
	q.push(topq);
	return out;
	
	
}

