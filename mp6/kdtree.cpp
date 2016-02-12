/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
 #include <math.h>

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    if(first[curDim]==second[curDim]){
          return first<second;
    }
    else {
        return first[curDim]<second[curDim];
    }
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    double dis1=0;
    double dis2=0;
    for(int i=0;i<Dim;i++){
        dis1+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
        dis2+=(potential[i]-target[i])*(potential[i]-target[i]);
    }
    
    if(dis1==dis2){
        return potential<currentBest;
    }
    else{
        return dis2<dis1;
    }

}


template<int Dim>
void KDTree<Dim>::swap(vector< Point<Dim> > & points,int lo, int hi)
{  
    Point<Dim> temp=points[lo];
    points[lo]=points[hi];
    points[hi]=temp;
}
 

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & points,int lo, int hi,int pivot,int curDim)
{  
     
    if(points.size()==1){
        return 0;
    }
     Point<Dim> target=points[pivot];

    swap(points,lo,pivot);

    int left=lo+1;
    int right=hi;

    while(left<right){
        if(smallerDimVal(target,points[left],curDim)){
       
              swap(points,left,right);
            right--;
        }
        else{
            left++;
        }
    }

    if(smallerDimVal(target,points[left],curDim)){
        left--;
        swap(points,lo,left);
        return left;
    }
    
    else{
        swap(points,lo,left);
        return left;
    }

}

   


template<int Dim>
void KDTree<Dim>::quickselect(vector< Point<Dim> > & points,int lo, int hi,int mid,int curDim)
{   
    if(hi>lo){
       
        int pivotpoint=(lo+hi)/2;
       int newPivotIndex=partition(points,lo,hi,pivotpoint,curDim);
        if(newPivotIndex==mid){
            return;
        }
        else if(newPivotIndex<mid){
            quickselect(points,newPivotIndex+1,hi,mid,curDim);
        }
        else{
            quickselect(points,lo,newPivotIndex-1,mid,curDim);
        }
    }
}



template<int Dim>
void KDTree<Dim>::buildTree(vector< Point<Dim> > & points,int lo, int hi,int curDim)
{   
    //base case
    if(lo>=hi){
        return;
    }
   
   
    int midianIndex=(lo+hi)/2;
    quickselect(points,lo,hi,midianIndex,curDim);
    buildTree(points,lo,midianIndex-1,(curDim+1)%Dim);
    buildTree(points,midianIndex+1,hi,(curDim+1)%Dim);
    
    
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
     
     if(newPoints.size()==0) return;
      for(int i=0;i<(int)newPoints.size();i++){
        points.push_back(newPoints[i]);
      }
      buildTree(points,0,points.size()-1,0);
}


template<int Dim>
double KDTree<Dim>::getRadius(const Point<Dim> & first,const Point<Dim> & second) const
{
    double out=0;
    for(int i=0;i<Dim;i++){
        out+=(first[i]-second[i])*(first[i]-second[i]);
    }
    return out;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{  
    
    int lo=0;
    int hi=points.size()-1;
  
    return findNearestNeighbor(query,lo,hi,0);
}


template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query,int lo,int hi,int curDim) const
{  
    
    if(lo>=hi){
        return points[lo];
    }

    int mid=(lo+hi)/2;
    Point<Dim> best;
    Point<Dim> target=points[mid];
    Point<Dim> besttemp;
    Point<Dim> besttemp2;
    bool left=false;
    bool right=false;

    if(smallerDimVal(query,target,curDim))
   
    {
        besttemp=findNearestNeighbor(query,lo,mid-1,(curDim+1)%Dim);
         left=true;
        right=false;
    }
    else{
        besttemp=findNearestNeighbor(query,mid+1,hi,(curDim+1)%Dim);
         left=false;
         right=true;
    }

    double besttempdis=getRadius(query,besttemp);

    double targetdis=(target[curDim]-query[curDim])*(target[curDim]-query[curDim]);
    
    if(shouldReplace(query,besttemp,target)){
        best=target;
        
    }
    else{
        best=besttemp;
    }

    if(targetdis<=besttempdis){
           
        if(left){
             besttemp2=findNearestNeighbor(query,mid+1,hi,(curDim+1)%Dim);
        }
        else{
              besttemp2=findNearestNeighbor(query,lo,mid-1,(curDim+1)%Dim);
        }
    
        if(shouldReplace(query,best,besttemp2)){
            best=besttemp2;
        }

    }

    
    
   return best;

}
