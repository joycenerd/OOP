#ifndef GFG_H
#define GFG_H
#include "fr.h"
using namespace std;


class GFG: public FR{
    public:
        GFG(){}
        GFG(int inId,double inX,double inY):FR(inId,inX,inY){}

};

#endif