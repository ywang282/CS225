#ifndef SCENE_H
#define SCENE_H
#include "image.h"
class Scene{

public:

            Scene (int max);
            ~Scene ();
 	    Scene (const Scene &source);
    const   Scene & operator= (const Scene &source);
    void    changemaxlayers (int newmax);
    void    addpicture (const char *FileName, int index, int x, int y);
    void    changelayer (int index, int newindex);
    void    translate (int index, int xcoord, int ycoord);
    void    deletepicture (int index);
    Image * getpicture (int index) const;
    Image   drawscene () const;
    
private:
    void copy(const Scene &source);
    void clear();
    int maxi;
    int * x;
    int * y;
    Image ** imagePointer;
};
#endif
