#ifndef GFGPACKET_H
#define GFGPACKET_H
#include "packet.h"


class GFGpacket:public Packet{
    public:
        GFGpacket(){}
        GFGpacket(int inSrc,int inDst,double inItxX,double inItxY):Packet(inSrc,inDst,inItxX,inItxY){};
    private:
        int mode;
};
#endif