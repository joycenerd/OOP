#include "node.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;


void Node::printNeighbor(){
    int vsize=0,i;
    vsize=planarGraph.size();
    printf("[%d] ",id);
    for(i=0;i<vsize;i++){
        printf("%d ",planarGraph[i].id);
    }
    printf("\n");
}

void Node::planarize(){
    int vsize,i,j,yn;
    double midX,midY,radius,distance;
    vsize=beforeNeighbor.size();
    for(i=0;i<vsize;i++){
        midX=(this->x+beforeNeighbor[i].x)/2;
        midY=(this->y+beforeNeighbor[i].y)/2;
        radius=sqrt(pow(midX-this->x,2)+pow(midY-this->y,2));
        yn=1;
        for(j=0;j<vsize;j++){
            if(j==i) continue;
            distance=sqrt(pow(midX-beforeNeighbor[j].x,2)+pow(midY-beforeNeighbor[j].y,2));
            if(distance<radius){
                yn=0;
                break;
            }
        }
        if(yn) planarGraph.push_back(beforeNeighbor[i]);
    }
}

void Node::addDst(int inDstId,double inDstX,double inDstY){
    dstId=inDstId;
    dstX=inDstX;
    dstY=inDstY;
}

// if queue isn't empty and also nextID is me
int Node::checkQueue(){
    Packet packet;
    int nextId;
    if(q_pkt.empty()) return -1;
    packet=q_pkt.front();
    nextId=packet.getNxtId();
    if(nextId==id){
        return id;
    }
    q_pkt.pop();
    return -1;
}

double arcCos(double curX,double curY,double prevX,double prevY,double nxtX,double nxtY){
    double aX,aY,bX,bY,aAbs,bAbs,degree;
    aX=prevX-curX;
    aY=prevY-curY;
    bX=nxtX-curX;
    bY=nxtY-curY;
    aAbs=sqrt(aX*aX+aY*aY);
    bAbs=sqrt(bX*bX+bY*bY);
    degree=acos((aX*bX+aY*bY)/(aAbs*bAbs));
    return degree;
}

bool sortBySec(const pair<int,double> &a,const pair<int,double> &b){
    return a.second<b.second;
}
// calculate slope of the given line by coordinates
double lineFunc(Node node,double lastX,double lastY){
    double curX,curY;
    curX=node.getX();
    curY=node.getY();
    double slope;
    slope=(lastY-curY)/(lastX-curX);
    return slope;
}

void getNewItx(double slope1,double x1,double y1,double slope2,double x2,double y2,double &newItxX,double &newitxY){
    newItxX=(-slope2*x2+y2+slope1*x1-y1)/(slope1-slope2);
    newitxY=slope1*(newItxX-x1)+y1;
    //printf("%f %f\n",newItxX,newitxY);
}

// case1: if the node is also an intersection point
void equalToItxCase(vector<Node> &planarGraph,double slope,Node node,Packet &packet,int plSide){
    int i,vsize,neighborId;
    double neighborX,neighborY,side,x,y,degree,dstX,dstY;
    vector<pair<int,double>> angle;
    vsize=planarGraph.size();
    for(i=0;i<vsize;i++){
        neighborId=planarGraph[i].getId();
        neighborX=planarGraph[i].getX();
        neighborY=planarGraph[i].getY();
        x=node.getX();
        y=node.getY();
        side=slope*(neighborX-x)-(neighborY-y);
        dstX=node.getDstX();
        dstY=node.getDstY();
        degree=arcCos(x,y,dstX,dstY,neighborX,neighborY);
        if((side>=0 && plSide==1) || (side<=0 && plSide==-1)) 
            angle.push_back(make_pair(neighborId,degree));
        else angle.push_back(make_pair(neighborId,2*M_PI-degree));
    }
    sort(angle.begin(),angle.end(),sortBySec);
    for(i=0;i<angle.size();i++) printf("%d %f\n",angle[i].first,angle[i].second);
    packet.modifyInfo(node.getId(),angle[0].first);
}

// other case: first find the node with smallest angle differnece form current node
int getSmallestAngle(vector<Node> &planarGraph,double lastX,double lastY,Node node,Packet &packet,int plSide,int vis[]){
    double slope,neighborX,neighborY,side,degree,x,y;
    int neighborId,vsize,i,lastId;
    vector<pair<int,double>> angle;
    angle.clear();
    vsize=planarGraph.size();
    x=node.getX();
    y=node.getY();
    lastId=packet.getLastId();
    for(i=0;i<vsize;i++){
        neighborId=planarGraph[i].getId();
        neighborX=planarGraph[i].getX();
        neighborY=planarGraph[i].getY();
        side=slope*(neighborX-x)-(neighborY-y);
        degree=arcCos(x,y,lastX,lastY,neighborX,neighborY);
        if(neighborId==lastId) angle.push_back(make_pair(neighborId,2*M_PI));
        else if((side<=0 && plSide==1) || (side>=0 && plSide==-1)) angle.push_back(make_pair(neighborId,degree));
        else angle.push_back(make_pair(neighborId,degree)); 
    }
    sort(angle.begin(),angle.end(),sortBySec);
    for(i=0;i<angle.size();i++) printf("%d %f\n",angle[i].first,angle[i].second);
    for(i=0;i<vsize;i++){
        neighborId=angle[i].first;
        if(vis[neighborId]==0) break;
    }
    return neighborId;
}

void Node::getNextHop(vector<Node> &v_nodes,int plSide){
    Packet packet;
    double itxX,itxY,slope,neighborX,neighborY,lastX,lastY,sdSlope;
    double curSide,neighborSide,isSame,newItxX,newItxY;
    vector<pair<int,double>> angle;
    int i,neighborId,lastId,srcId;
    int vis[1010];
    printf("%d\n",id);
    packet=q_pkt.front();
    itxX=packet.getItxX();
    itxY=packet.getItxY();
    srcId=packet.getSrcId();
    // get source-destination function
    sdSlope=lineFunc(v_nodes[srcId],dstX,dstY);
    if(x==itxX && y==itxY){
        equalToItxCase(planarGraph,sdSlope,v_nodes[id],packet,plSide);
        q_pkt.pop();
        q_pkt.push(packet);
        return;
    }
    lastId=packet.getLastId();
    lastX=v_nodes[lastId].x;
    lastY=v_nodes[lastId].y;
    for(i=0;i<1010;i++) vis[i]=0;
    while(1){
        // find samllest angle
        neighborId=getSmallestAngle(planarGraph,lastX,lastY,v_nodes[id],packet,plSide,vis);
        neighborX=v_nodes[neighborId].x;
        neighborY=v_nodes[neighborId].y;
        curSide=sdSlope*(x-dstX)-(y-dstY);
        neighborSide=sdSlope*(neighborX-dstX)-(neighborY-dstY);
        isSame=curSide*neighborSide;
        // case 2: if neighbor and current node is on the same side
        if(isSame>=0){
             q_pkt.pop();
             packet.modifyInfo(id,neighborId);
            q_pkt.push(packet);
            return;
        }
        // if neighbor cross line get new intersection point
        slope=lineFunc(v_nodes[neighborId],x,y);
        getNewItx(sdSlope,dstX,dstY,slope,x,y,newItxX,newItxY);
        // case 3: neighbor and current node is on the opposite side but neighbor is on the left side of source dextination line
        if(neighborSide>=0){
            q_pkt.pop();
            packet.modifyInfo(id,neighborId);
            packet.updateItx(newItxX,newItxY);
            q_pkt.push(packet);
            return;
        }
        // case 4: if intersection point isn't the newest, than cross the line 
        if((dstX>x && newItxX<=itxX && newItxY<=itxY) || (dstX<x && newItxX>=itxX && newItxY>=itxY)){
            q_pkt.pop();
             packet.modifyInfo(id,neighborId);
            q_pkt.push(packet);
            return;
        }
        packet.updateItx(newItxX,newItxY);
        lastX=newItxX;
        lastY=newItxY;
        //printf("%f %f\n",lastX,lastY);
        vis[neighborId]=1;
    }
    angle.clear();
}

// send packet
void Node::send(vector<Node> &v_nodes){
    int vsize,i,neighborId;
    Packet packet;
    vsize=beforeNeighbor.size();
    packet=v_nodes[id].q_pkt.front();
    //printf("%d ",packet.getLastId());
    v_nodes[id].q_pkt.pop();
    for(i=0;i<vsize;i++){
        neighborId=beforeNeighbor[i].getId();
        v_nodes[neighborId].q_pkt.push(packet);
    }
}