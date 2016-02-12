#include "image.h"


void Image::flipleft(){
RGBAPixel* temp=new RGBAPixel;
    for(size_t i=0;i<this->width()/2;i++){
        for(size_t j=0;j<this->height();j++){
            *temp=*(*this)(this->width()-i-1,j);
            *(*this)(this->width()-1-i,j)=*(*this)(i,j);
            *(*this)(i,j)=*temp;
         } 
    }
delete temp;
}



void Image::adjustbrightness(int r, int g, int b){
     for(size_t i=0;i<this->width();i++){
        for(size_t j=0;j<this->height();j++){
            RGBAPixel * pixel=(*this)(i,j);

            if(pixel->red+r<0){ pixel->red=0; }
            else if(pixel->red+r>255){pixel->red=255;}
            else {pixel->red=r+pixel->red;}

            if(pixel->green+g<0){ pixel->green=0; }
            else if(pixel->green+g>255){pixel->green=255;}
            else {pixel->green=g+pixel->green;}

            if(pixel->blue+b<0){ pixel->blue=0; }
            else if(pixel->blue+b>255){pixel->blue=255;}
            else {pixel->blue=b+pixel->blue;}
          }
     }

}	



void Image::invertcolors(){
            for(size_t i=0;i<this->width();i++){
                 for(size_t j=0;j<this->height();j++){
                      (*this)(i,j)->red=255-(*this)(i,j)->red;
                      (*this)(i,j)->green=255-(*this)(i,j)->green;
                      (*this)(i,j)->blue=255-(*this)(i,j)->blue;
                 }
            }
}





