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
        void pushNeighbor(Node node){beforeNeighbor.push_back(node);};
        void printNeighbor();
        void planarize();
        void initPkt(Packet packet){q_pkt.push(packet);};
        int checkQueue();
        void getNextHop();

    private:
        int id;
        double x;
        double y;
        vector<Node> beforeNeighbor;
        vector<Node> planarGraph;
        queue<Packet> q_pkt;
};

#endif