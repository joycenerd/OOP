#ifndef NODE_H
#define NODE_H
#include "packet.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Node{

    public:
        Node();
        Node(int inId,double inX,double inY):id(inId),x(inX),y(inY){};
        int getId(){return id;};
        double getX(){return x;};
        double getY(){return y;};
        double getDstX(){return dstX;};
        double getDstY(){return dstY;};
        void pushNeighbor(Node node){beforeNeighbor.push_back(node);};
        void printNeighbor();
        void planarize();
        void addDst(int inDstId,double inDstX,double inDstY);
        void initPkt(Packet packet){q_pkt.push(packet);};
        int checkQueue();
        void getNextHop(vector<Node> &v_nodes,int plSide);
        void send(vector<Node> &v_nodes);

    private:
        int id;
        double x;
        double y;
        int dstId;
        double dstX;
        double dstY;
        vector<Node> beforeNeighbor;
        vector<Node> planarGraph;
        queue<Packet> q_pkt;
};

#endif