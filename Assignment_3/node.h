#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
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

    private:
        int id;
        double x;
        double y;
        vector<Node> beforeNeighbor;
        vector<Node> planarGraph;
};

#endif