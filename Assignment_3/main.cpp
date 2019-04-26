#include "node.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

void inputData(FILE *fin,vector<Node> &v_nodes){
    int id,i;
    double x,y;
    int numOfNodes;
    fscanf(fin,"%d",&numOfNodes);
    for(i=0;i<numOfNodes;i++){
        fscanf(fin,"%d %lf %lf",&id,&x,&y);
        Node node(id,x,y);
        v_nodes.push_back(node);
    }
}

void addNeighbor(vector<Node> &v_nodes,int vsize){
    int i,j,aId,bId;
    double aX,aY,bX,bY,distance;
    for(i=0;i<vsize;i++){
        aId=v_nodes[i].getId();
        aX=v_nodes[i].getX();
        aY=v_nodes[i].getY();
        for(j=i+1;j<vsize;j++){
            bId=v_nodes[j].getId();
            bX=v_nodes[j].getX();
            bY=v_nodes[j].getY();
            distance=sqrt(pow(aX-bX,2)+pow(aY-bY,2));
            if(distance<=1){
                v_nodes[i].pushNeighbor(v_nodes[j]);
                v_nodes[j].pushNeighbor(v_nodes[i]);
            }
        }
    }
}


int main(int argc, char **argv)
{
    FILE *fin=fopen(argv[1],"r");
    int numOfNodes=0,id,i,vsize;
    double x,y;
    vector<Node> v_nodes;
    v_nodes.reserve(1010);
    inputData(fin,v_nodes);
    vsize=v_nodes.size();
    addNeighbor(v_nodes,vsize);
    for(i=0;i<vsize;i++) v_nodes[i].planarize();
    for(i=0;i<vsize;i++) v_nodes[i].printNeighbor();
}