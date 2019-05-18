#ifndef PACKET_H
#define PACKET_H
#include <iostream>
using namespace std;


class Packet{
    public:
        Packet(){};
        Packet(int inSrc,int inDst,double inItxX,double inItxY);
        int getNxtId(){return nextId;};
        double getItxX(){return itxX;};
        double getItxY(){return itxY;};
        double getSlope(){return slope;};
        int getDstId(){return dstId;};
        void modifyInfo(int cur,int nexts);
        int getLastId(){return lastId;};
        void updateItx(double newX,double newY);
        int getSrcId(){return srcId;};
            
    private:
        int srcId;
        int dstId;
        int lastId;
        int nextId;
        double itxX;
        double itxY;
        double slope;
};

#endif
        