#ifndef GFGPACKET_H
#define GFGPACKET_H
#include "packet.h"


class GFGpacket:public Packet{
    public:
        GFGpacket(){}
        GFGpacket(int inSrc,int inDst,double inItxX,double inItxY):
            Packet(inSrc,inDst,inItxX,inItxY),mode(1),minDist(10000){};
        int getMode(){return mode;}
        void rstSrcId(int newId){};
        double getDist(){return minDist;}
        void rstDist(double mini){minDist=mini;}
        void setmod(int newmod){mode=newmod;}
    private:
        int mode;
        double minDist;
};
#endif