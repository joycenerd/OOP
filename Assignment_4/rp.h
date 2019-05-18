#ifndef RP_H
#define RP_H
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class RP{
    public:
        RP();
        RP(int inId,double inX,double inY):id(inId),x(inX),y(inY){};
        int getId(){return id;};
        double getX(){return x;};
        double getY(){return y;};
        void pushNeighbor(RP node){beforeNeighbor.push_back(node);};
        void planarize();
        void printNeighbor();
        void getNextHop();
        void addDst(int inDstId,double inDstX,double inDstY);
    private:
        int id;
        double x;
        double y;
        int dstId;
        double dstX;
        double dstY;
        vector<RP> beforeNeighbor;
        vector<RP> planarGraph;
};

#endif
