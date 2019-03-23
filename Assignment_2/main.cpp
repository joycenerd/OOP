#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "request.h"
#include "resource.h"
#include <vector>
#define MAX_SIZE 1000
using namespace std;




int main()
{
  FILE *fin = fopen("./request.txt", "r");
  int timeSlots = 0, timeSlotID = 0, requestNum = 0, resourceNum = 0;
  int requestId=0,resourceId=0;
  int edges=0,edgeId=0;
  int i=0;
  vector<Request> v_request;
  vector<Resource> v_resource;
  Request request;
  Resource resource;
  bool yn,isAlloc;

  // read data from file
  fscanf(fin, "%d", &timeSlots);
  while (timeSlots--) {
    fscanf(fin, "%d %d %d", &timeSlotID, &requestNum, &resourceNum);
    while(requestNum--){
        fscanf(fin,"%d",&requestId);
        request(requestId);
        v_request.push_back(request);
    }
    while(resourceNum--){
        fscanf(fin,"%d",&resourceId);
        resource(resourceId);
        v_resource.push_back(resource);
    }
    fscanf(fin,"%d",&edges);
    while(edges--){
        fscanf(fin,"%d %d %d\n",&edgeId,&requestId,&resourceId);
        yn=v_resource[resourceId]->*requestId;
        if(yn) doMatching(requestId);
    }
    for(i=0;i<v_resource.size();i++){
        yn=v_resource[i].checkMatched();
        if(!yn){
            isAlloc=v_resource[i].allocateResource();
        }
    }
  }

}