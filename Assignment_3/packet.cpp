#include "packet.h"

Packet::Packet(int inSrc,int inDst,double inItxX,double inItxY,double inSlope){
    srcId=inSrc;
    dstId=inDst;
    lastId=nextId=srcId;
    itxX=inItxX;
    itxY=inItxY;
    slope=inSlope;
}