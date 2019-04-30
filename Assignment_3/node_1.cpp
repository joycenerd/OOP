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
    int i,vsize,neighborId,lastId;
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
    for(i=0;i<angle.size();i++) printf("case1=%d %f\n",angle[i].first,angle[i].second);
    packet.modifyInfo(node.getId(),angle[0].first);
}

// other case: first find the node with smallest angle differnece form current node
int getSmallestAngle(vector<Node> &planarGraph,double lastX,double lastY,Node node,Packet &packet,int plSide,int vis[],int srcSide){
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
        else if(side<=0 && plSide==1 && srcSide==1) angle.push_back(make_pair(neighborId,degree));
        else if(side>=0 && plSide==-1 && srcSide==-1) angle.push_back(make_pair(neighborId,degree));
        else angle.push_back(make_pair(neighborId,2*M_PI-degree)); 
    }
    sort(angle.begin(),angle.end(),sortBySec);
    printf("angle size=%d\n",angle.size());
    for(i=0;i<angle.size();i++){
        printf("case2=%d %f\n",angle[i].first,angle[i].second);
        //printf("%d %d\n",plSide,srcSide);
    }
    for(i=0;i<vsize;i++){
        neighborId=angle[i].first;
        if(vis[neighborId]==0) break;
    }
    return neighborId;
}

void Node::getNextHop(vector<Node> &v_nodes,int plSide,int srcSide){
    double itxX,itxY,degree,nxtX,nxtY,slope,side,dir,crossing,curSide,nxtSide,sdSlope;
    double crossing;
    int i,vsize,srcId,nxtId;
    vector<pair<int,double>> angle;
    Packet packet=q_pkt.front();
    itxX=packet.getItxX();
    itxY=packet.getItxY();
    vsize=planarGraph.size();
    angle.clear();
    if(x==itxX && y==itxY){
        for(i=0;i<vsize;i++){
            nxtX=planarGraph[i].x;
            nxtY=planarGraph[i].y;
            degree=arcCos(x,y,dstX,dstY,nxtX,nxtY);
            slope=lineFunc(*this,dstX,dstY);
            side=slope*(nxtX-x)-(nxtY-y);
            dir=dstX-x;
            if(packet.getLastId()==planarGraph[i].id) degree=2*M_PI;
            else if(dir>=0){
                if(side<0) degree=2*M_PI-degree;
            }
            else if(dir<0){
                if(side>0) degree=2*M_PI-degree;
            }
            angle.push_back(make_pair(planarGraph[i].id,degree));
        }
        sort(angle.begin(),angle.end(),sortBySec);
        packet.modifyInfo(id,angle[0].first);
        q_pkt.pop();
        q_pkt.push(packet);
        return;
    }
    srcId=packet.getSrcId();
    sdSlope=lineFunc(v_nodes[srcId],dstX,dstY);
    for(i=0;i<vsize;i++){
        nxtX=planarGraph[i].x;
        nxtY=planarGraph[i].y;
        degree=arcCos(x,y,dstX,dstY,nxtX,nxtY);
        slope=lineFunc(*this,dstX,dstY);
        side=slope*(nxtX-x)-(nxtY-y);
        dir=dstX-x;
        if(packet.getLastId()==planarGraph[i].id) degree=2*M_PI;
        else if(dir>=0){
            if(side<0) degree=2*M_PI-degree;
        }
        else if(dir<0){
            if(side>0) degree=2*M_PI-degree;
        }
        angle.push_back(make_pair(planarGraph[i].id,degree));
    }
    sort(angle.begin(),angle.end(),sortBySec);
    nxtId=angle[0].first;
    nxtX=v_nodes[nxtId].x;
    nxtY=v_nodes[nxtId].y;
    curSide=sdSlope*(x-dstX)-(y-dstY);
    nxtSide=sdSlope*(nxtX-dstX)-(nxtY-dstY);
    crossing=curSide*nxtSide;
    if(crossing>=0){
        packet.modifyInfo(id,nxtId);
        q_pkt.pop();
        q_pkt.push(packet);
        return;
    }
    slope=lineFunc(v_nodes[nxtId],x,y);
    itxX=(-slope*x+y+sdSlope*dstX-dstY)/(sdSlope-slope);
    itxY=sdSlope*(itxX-dstX)+dstY;
    packet.updateItx(itxX,itxY);
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