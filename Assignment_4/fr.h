#ifndef FR_H
#define FR_H
#include "rp.h"
#include "gfgpacket.h"
//#include "gfg.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

class FR: public RP{
    public:
        friend class GFG;
        FR(){}
        FR(int inId,double inX,double inY):id(inId),x(inX),y(inY){}
        int getId(){return id;}
        double getX(){return x;}
        double getY(){return y;}
        void addDst(int inDstId,double inDstX,double inDstY);
        void initPkt(GFGpacket packet){q_pkt.push(packet);}
        int checkQueue();
        void pushNeighbor(FR node){beforeNeighbor.push_back(node);}
        void planarize();
        void printNeighbor();
        void getNextHop(vector<FR> &v_nodes);
    private:
        int id;
        double x;
        double y;
        int dstId;
        double dstX;
        double dstY;
        vector<FR> beforeNeighbor;
        vector<FR> planarGraph;
        queue<GFGpacket> q_pkt;
};

#endif