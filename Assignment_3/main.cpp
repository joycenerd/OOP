#include "node.h"
#include "packet.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

// input node information
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

// add neighbor is distance <= 1
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

void faceRouting(vector<Node> v_nodes,int vsize,int srcId,int dstId,FILE *fout){
    double itxX,itxY,slope,dstX,dstY,srcX;
    int i,curId,isMine,plSide,lastId,srcSide;
    dstX=v_nodes[dstId].getX();
    dstY=v_nodes[dstId].getY();
    srcX=v_nodes[srcId].getX();
    for(i=0;i<vsize;i++) v_nodes[i].addDst(dstId,dstX,dstY);
    itxX=v_nodes[srcId].getX();
    itxY=v_nodes[srcId].getY();
    // initialize packet and add to the queue of source
    Packet packet(srcId,dstId,itxX,itxY);
    v_nodes[srcId].initPkt(packet);
    if(srcX<dstX) plSide=1;
    else plSide=-1;
   while(1){
       //printf("yes\n");
       for(i=0;i<vsize;i++){
           isMine=v_nodes[i].checkQueue();
           if(isMine!=-1){
               curId=isMine;
           }
       }
       // record packet route
       fprintf(fout,"%d ",curId);
       // end if packet has send to destination
       if(curId==dstId) break;
       v_nodes[curId].getNextHop(v_nodes,plSide,srcSide);
       v_nodes[curId].send(v_nodes);
       if(v_nodes[curId].getX()>=v_nodes[srcId].getX()) srcSide=1;
       else srcSide=-1; 
       printf("\n");
   }
   fprintf(fout,"\n");
}


int main(int argc, char **argv)
{
    FILE *fin=fopen(argv[1],"r");
    FILE *fout=fopen("./result.txt","w");
    int numOfNodes=0,id,i,vsize,pairs,srcId,dstId;
    double x,y;
    vector<Node> v_nodes;
    v_nodes.reserve(1010);
    inputData(fin,v_nodes);
    vsize=v_nodes.size();
    // link nodes with distance<=1
    addNeighbor(v_nodes,vsize);
    // planar graph
    for(i=0;i<vsize;i++) v_nodes[i].planarize();
    fscanf(fin,"%d",&pairs);
    for(i=0;i<pairs;i++){
        fscanf(fin,"%d %d",&srcId,&dstId);
        faceRouting(v_nodes,vsize,srcId,dstId,fout);
    }
    return 0;
}