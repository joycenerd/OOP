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


typedef struct{
    int acceptID;
    int flowPath[N];
}ACCEPTPATH;
ACCEPTPATH flowPath[N];
int acceptFlows=0;

int checkFlow(int graph[N][N],int tail,int path[],int flowSize){
    return **graph;
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
        if(dist[i]<mini){
            index=i;
            mini=dist[i];
        }
    }
    return index;
}

void ShortestPath(int graph[N][N],int nodes,int flowID,int sourceID,int destinationID, int flowSize){
    int visit[N]={0};
    int dist[N],path[N][N]={0},tail[N];
    int i;
    for(i=0;i<nodes;i++) tail[i]=-1;
    for(i=0;i<nodes;i++){
        dist[i]=graph[sourceID][i];
        if(dist[i]<MAX_COST){
            path[i][0]=sourceID;
            path[i][1]=i;
            tail[i]=1;
        }
    }
    visit[sourceID]=1;
    for(i=0;i<nodes-2;i++){
        int next=choose(dist,nodes,visit);
        visit[next]=1;
        for(int u=0;u<nodes;u++){
            if(!visit[u] && dist[next]+graph[next][u]<dist[u]){
                dist[u]=dist[next]+graph[next][u];
                memset(path[u],0,sizeof(path[u]));
                *path[u]=CopyList(path[next],path[u],tail[next],u);
                tail[u]=tail[next]+1;
            }
        }
    }
    **graph=checkFlow(graph,tail[destinationID],path[destinationID],flowSize);
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
    int graph[N][N];
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++) graph[i][j]=MAX_COST;
    }
    while(directedLinks--){
        fin >> linkID >> firstNode >> secondNode >> linkCapacity;
        graph[firstNode][secondNode]=linkCapacity;
    }
    fin >> requestFlows;
    while(requestFlows--){
        fin >> flowID >> sourceID >> destinationID >> flowSize;
        ShortestPath(graph,nodes,flowID,sourceID,destinationID,flowSize);
        break;
    }
    return 0;
}
