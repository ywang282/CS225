#include<iostream>
#include "scene.h"
using namespace std;

void Scene::copy(const Scene & source){
    maxi=source.maxi;
    x=new int[source.maxi];
    y=new int[source.maxi];
    if(source.imagePointer==NULL){imagePointer=NULL;}
    else {imagePointer=new Image*[maxi];
          for(int i=0;i<source.maxi;i++){
              if(source.imagePointer[i]==NULL){
                 imagePointer[i]=NULL;
                 x[i]=0;
                 y[i]=0;
              }
              else {imagePointer[i]=new Image;
                    *imagePointer[i]=*source.imagePointer[i];
                    x[i]=source.x[i]; 
                    y[i]=source.y[i];
              }
          }

     }
}

void Scene::clear(){
       if(imagePointer!=NULL){
          for (int i=0;i<maxi;i++){
              if(imagePointer[i]!=NULL){
              delete imagePointer[i];
              }
           }
        delete [] imagePointer;
        delete []x;
        delete []y;
       }
}


Scene::Scene(int max){
    maxi=max;
    x=new int[max];
    y=new int[max];
    imagePointer=new Image*[max];
    for (int i=0; i<max;i++) {
        imagePointer[i]=NULL;
        x[i]=0;
        y[i]=0;
    }
    
}

Scene::Scene(const Scene & source){    
copy(source);
}

Scene::~Scene(){
  clear();
}



//***dazhi**************************************************************************************************************
const Scene & Scene::operator=(const Scene & source){
    if (this != &source){
		clear();
		copy(source);
	}
	return *this;}

void Scene::changemaxlayers	(int newmax){
    if(newmax>=maxi){
        Image ** newImagePointer=new Image*[newmax];
        
        //maxi=newmax;
        int * c=new int[newmax];
        int * d=new int[newmax];
        for (int i=0; i<maxi; i++) {
            if (imagePointer[i]!=NULL){
            newImagePointer[i]=imagePointer[i];
            c[i]=x[i];
            d[i]=y[i];
            }
            else {newImagePointer[i]=NULL;
                  c[i]=0;
		  d[i]=0;
            }
        }
        for(int i=maxi;i<newmax;i++){ 
            newImagePointer[i]=NULL;
            c[i]=0;
            d[i]=0;
        }
        
        delete [] imagePointer;
        imagePointer=newImagePointer;
        delete []x;
        delete []y;
        x=c;
        y=d;
        maxi=newmax;
        
    }
    
    else {for (int i=newmax; i<maxi; i++) {
                if (imagePointer[i]!=NULL){
                    cout << "invalid newmax" << endl;
                    return;
                }
           }
        Image **newImagePointer=new Image*[newmax];
        int * c=new int[newmax];
        int * d=new int[newmax];
        for (int i=0; i<newmax; i++) {
            if(imagePointer[i]==NULL){newImagePointer[i]=NULL;c[i]=0;d[i]=0;}
            else {newImagePointer[i]=imagePointer[i];
                   c[i]=x[i];
                   d[i]=y[i];
            }
        }
        
        delete [] imagePointer;
        delete [] x;
        delete [] y;
        imagePointer=newImagePointer;
        x=c;
        y=d;
        maxi=newmax;
    }

}

void Scene::addpicture	(const char * FileName, int index, int x, int y){
    if (index >=maxi || index < 0) {
		cout << "index out of bounds" << endl;
                return;
	}
    if(imagePointer[index]==NULL){
        imagePointer[index] = new Image;
        imagePointer[index]->readFromFile(FileName);
        this->x[index] = x;
        this->y[index] = y;
    }
    else if(imagePointer[index]!=NULL){
        delete imagePointer[index];
        imagePointer[index] = new Image;
        imagePointer[index]->readFromFile(FileName);
        this->x[index] = x;
        this->y[index] = y;
    }
}

void Scene::changelayer	(int index,int newindex){
    if (index == newindex) return;
	
    if (index >= maxi || index < 0 || newindex >= maxi || newindex < 0) {
		cout << "invalid index" << endl;
		return;
	}
    if (imagePointer[index]!=NULL) {
        if (imagePointer[newindex]==NULL) {
        imagePointer[newindex]=new Image;
        *imagePointer[newindex] = *imagePointer[index];
        x[newindex] = x[index];
        y[newindex] = y[index];
        delete imagePointer[index];
        x[index]=0;y[index]=0;
        imagePointer[index]=NULL;
        
       }
	   
       else if(imagePointer[newindex]!=NULL){
               delete imagePointer[newindex];
               imagePointer[newindex]=new Image;
	       *imagePointer[newindex] = *imagePointer[index];
	       x[newindex] = x[index];
	       y[newindex] = y[index];
               delete imagePointer[index];
               x[index]=0;y[index]=0;
               imagePointer[index]=NULL;
       }
   }
    else if (imagePointer[index]==NULL) {
         if(imagePointer[newindex]!=NULL){
         delete imagePointer[newindex];
         imagePointer[newindex]=NULL;x[newindex]=0;y[newindex]=0;
         }
    }
}

void Scene::translate (int index, int xcoord, int ycoord){
    if (index >= maxi|| index < 0 || imagePointer[index] == NULL) {
		cout << "invalid index" << endl;
		return;
    }
	
	x[index] = xcoord;
	y[index] = ycoord;
}

void Scene::deletepicture(int index){
    if (index >= maxi|| index < 0 || imagePointer[index] == NULL) {
		cout << "invalid index" << endl;
		return;
	}
	
	delete imagePointer[index];
	imagePointer[index] = NULL;
        x[index]=0;y[index]=0;
}


Image * Scene::getpicture (int index)const{
    if (index >= maxi|| index < 0 || imagePointer[index] == NULL) {
		cout << "invalid index" << endl;
		return NULL;
    }
	
    return imagePointer[index];
}





Image Scene::drawscene()const{
    size_t maxWidth = 0;
    size_t maxHeight = 0;
    for (int i = 0; i < maxi; i++) {
	if (imagePointer[i] != NULL) {
	   if ((imagePointer[i]->width() + x[i]) > maxWidth) {
                maxWidth = (imagePointer[i]->width() + x[i]);
	   }
	   if ((imagePointer[i]->height() + y[i]) > maxHeight) {
                maxHeight = (imagePointer[i]->height() + y[i]);
	   }
	}
    }
	
    Image out;
    out.resize(maxWidth, maxHeight);
	
    for (int i = 0; i < maxi; i++) {
		
		if (imagePointer[i] != NULL) {
			for (size_t j = 0; j < imagePointer[i]->width(); j++) {
				for (size_t k = 0; k < imagePointer[i]->height(); k++) {
                                     *(out)(x[i]+j, y[i]+k) = *(*(imagePointer[i]))(j,k);
                                                  //*(*imagePointer[i])(j,k);
				}
			}
		}
     }
	
     return out;
    
}

