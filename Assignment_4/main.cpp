#include "rp.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

void inputData(FILE *fin,vector<RP> &v_nodes){
    int id,i;
    double x,y;
    int numOfNodes;
    fscanf(fin,"%d",&numOfNodes);
    for(i=0;i<numOfNodes;i++){
        fscanf(fin,"%d%lf%lf",&id,&x,&y);
        RP node(id,x,y);
        v_nodes.push_back(node);
    }
}

// add neightbor if distance <= 1
void addNeighbor(vector<RP> &v_nodes,int vsize){
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
            //printf("%d %d %f\n",aId,bId,distance);
            if(distance<=1 || fabs(distance-1)<=0.000001){
                //printf("%d %d\n",i,j);
                v_nodes[i].pushNeighbor(v_nodes[j]);
                v_nodes[j].pushNeighbor(v_nodes[i]);
            }
        }
    }
}

void routing(vector<RP> v_nodes,int vsize,int srcId,int dstId,FILE *fout){
    double itxX,itxY,slope,dstX,dstY,srcX;
    int i,curId,isMine,lastId;
    dstX=v_nodes[dstId].getX();
    dstY=v_nodes[dstId].getY();
    srcX=v_nodes[srcId].getX();
    //printf("%f\n%f %f\n",srcX,dstX,dstY);
    for(i=0;i<vsize;i++) v_nodes[i].addDst(dstId,dstX,dstY);
}

int main(int argc,char *argv[])
{
    FILE *fin=fopen(argv[1],"r");
    FILE *fout=fopen("./result.txt","w");
    int numOfNodes,id,i,vsize,srcId,dstId,pairs;
    double x,y;
    vector<RP>v_nodes;
    v_nodes.reserve(1010);
    inputData(fin,v_nodes);
    vsize=v_nodes.size();
    // link nodes with distance<=1
    addNeighbor(v_nodes,vsize);
    // planar graph
    for(i=0;i<vsize;i++) v_nodes[i].planarize();
    for(i=0;i<vsize;i++) v_nodes[i].printNeighbor();
    fscanf(fin,"%d",&pairs);
    for(i=0;i<pairs;i++){
        fscanf(fin,"%d%d",&srcId,&dstId);
        routing(v_nodes,vsize,srcId,dstId,fout);
    }
    return 0;
}
