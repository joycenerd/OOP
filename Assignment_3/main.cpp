#include "node.h"
#include "packet.h"
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
double calcSlope(Node source,Node destination){
    double srcX,srcY,dstX,dstY,slope;
    srcX=source.getX();
    srcY=source.getY();
    dstX=destination.getX();
    dstY=destination.getY();
    slope=(dstY-srcY)/(dstX-srcX);
    return slope;
}


void faceRouting(vector<Node> &v_nodes,int vsize,int srcId,int dstId){
    double itxX,itxY,slope,dstX,dstY;
    int i,curId,isMine;
    dstX=v_nodes[dstId].getX();
    dstY=v_nodes[dstId].getY();
    for(i=0;i<vsize;i++) v_nodes[i].addDst(dstId,dstX,dstY);
    itxX=v_nodes[srcId].getX();
    itxY=v_nodes[srcId].getY();
    slope=calcSlope(v_nodes[srcId],v_nodes[dstId]);
    Packet packet(srcId,dstId,itxX,itxY,slope);
    v_nodes[srcId].initPkt(packet);
   while(1){
       for(i=0;i<vsize;i++){
           isMine=v_nodes[i].checkQueue(0);
           if(isMine!=-1) curId=isMine;
       }
       int nxtId=v_nodes[curId].getNextHop();
       packet.goNxt(nxtId);
       printf("%d\n",packet.getNxtId());
       break;
   }
}


int main(int argc, char **argv)
{
    FILE *fin=fopen(argv[1],"r");
    int numOfNodes=0,id,i,vsize,pairs,srcId,dstId;
    double x,y;
    vector<Node> v_nodes;
    v_nodes.reserve(1010);
    inputData(fin,v_nodes);
    vsize=v_nodes.size();
    addNeighbor(v_nodes,vsize);
    for(i=0;i<vsize;i++) v_nodes[i].planarize();
    fscanf(fin,"%d",&pairs);
    for(i=0;i<pairs;i++){
        fscanf(fin,"%d %d",&srcId,&dstId);
        faceRouting(v_nodes,vsize,srcId,dstId);
    }
}