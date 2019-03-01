//
//  main.cpp
//  Assignement_1-FlowAcceptance
//
//  Created by Joyce Chin on 2019/2/28.
//  Copyright © 2019 Joyce Chin. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <fstream>
#define N 200
#define MAX_COST 100000
using namespace std;


int link[N][N];
double cost[N][N];

typedef struct{
    int acceptID;
    int pathLenth;
    int flowPath[N];
}ACCEPTPATH;
ACCEPTPATH accept[N];
int acceptFlows=0,throughPut=0;

void CheckandUpdate(int flowID,int path[],int tail,int flowSize){
    int from,to,i;
    from=path[0];
    for(i=1;i<=tail;i++){
        to=path[i];
        if(link[from][to]-flowSize<0) return;
        from=to;
    }
    accept[acceptFlows].acceptID=flowID;
    from=accept[acceptFlows].flowPath[0]=path[0];
    accept[acceptFlows].pathLenth=tail;
    for(i=1;i<=tail;i++){
        to=accept[acceptFlows].flowPath[i]=path[i];
        link[from][to]-=flowSize;
        if(link[from][to]==0) cost[from][to]=MAX_COST;
        else cost[from][to]=(double)flowSize/link[from][to];
        from=to;
    }
    throughPut+=flowSize;
    acceptFlows++;
}

int CopyList(int from[],int to[],int tail,int end){
    for(int i=0;i<=tail;i++) to[i]=from[i];
    to[++tail]=end;
    return *to;
}

int choose(int dist[],int nodes,int visit[]){
    int mini=MAX_COST;
    int index=-1;
    for(int i=0;i<nodes;i++){
        if(!visit[i] && dist[i]<mini){
            index=i;
            mini=dist[i];
        }
    }
    return index;
}

void ShortestPath(int nodes,int flowID,int sourceID,int destinationID, int flowSize){
    int visit[N]={0};
    int dist[N],path[N][N]={0},tail[N];
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++) path[i][j]=0;
    }
    for(i=0;i<nodes;i++) tail[i]=-1;
    for(i=0;i<nodes;i++){
        dist[i]=cost[sourceID][i];
        if(dist[i]<MAX_COST){
            path[i][0]=sourceID;
            path[i][1]=i;
            tail[i]=1;
        }
    }
    visit[sourceID]=1;
    for(i=0;i<nodes-2;i++){
        int next=choose(dist,nodes,visit);
        if(next==-1) break;
        visit[next]=1;
        for(int u=0;u<nodes;u++){
            if(!visit[u] && dist[next]+cost[next][u]<dist[u]){
                dist[u]=dist[next]+cost[next][u];
                memset(path[u],0,sizeof(path[u]));
                *path[u]=CopyList(path[next],path[u],tail[next],u);
                tail[u]=tail[next]+1;
            }
        }
    }
    if(tail[destinationID]==-1) return;
    CheckandUpdate(flowID,path[destinationID],tail[destinationID],flowSize);
}


int main()
{
    int nodes,directedLinks,linkID,firstNode,secondNode,linkCapacity;
    int requestFlows,flowID,sourceID,destinationID,flowSize;
    ifstream fin;
    ofstream fout;
    fout.open("result.txt");
    fin.open("request.txt");
    fin >> nodes >> directedLinks;
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++) cost[i][j]=MAX_COST;
    }
    while(directedLinks--){
        fin >> linkID >> firstNode >> secondNode >> linkCapacity;
        link[firstNode][secondNode]=cost[firstNode][secondNode]=linkCapacity;
    }
    fin >> requestFlows;
    while(requestFlows--){
        fin >> flowID >> sourceID >> destinationID >> flowSize;
        ShortestPath(nodes,flowID,sourceID,destinationID,flowSize);
    }
    fout << acceptFlows << " " << throughPut << endl;
    for(i=0;i<acceptFlows;i++){
        fout << accept[i].acceptID;
        for(j=0;j<=accept[i].pathLenth;j++){
            if(j==accept[i].pathLenth) fout << " " <<accept[i].flowPath[j] << endl;
            else fout << " " << accept[i].flowPath[j];
        }
    }
    return 0;
}
