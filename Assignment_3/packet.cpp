#include "packet.h"

Packet::Packet(int inSrc,int inDst,double inItxX,double inItxY){
    srcId=inSrc;
    dstId=inDst;
    lastId=nextId=srcId;
    itxX=inItxX;
    itxY=inItxY;
}

void Packet::modifyInfo(int cur,int nexts){
    lastId=cur;
    nextId=nexts;
}

void Packet::updateItx(double newX,double newY){
    itxX=newX;
    itxY=newY;
}