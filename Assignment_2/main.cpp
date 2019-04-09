#include "request.h"
#include "resource.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  FILE *fin = fopen(argv[1], "r");
  FILE *fout = fopen("./result.txt", "w");
  int timeSlots = 0, timeSlotID = 0, requestNum = 0, resourceNum = 0;
  int requestId = 0, resourceId = 0;
  int edges = 0, edgeId = 0,cnt=0;
  static int satisfiedRequests;
  int i = 0;
  vector<Request> v_request;
  vector<Resource> v_resource;
  bool yn, isAlloc;
  v_request.reserve(1010);
  v_resource.reserve(1010);
  v_request.clear();

  // read request and resource
  fscanf(fin, "%d", &timeSlots);
  while (timeSlots--) {
    fscanf(fin, "%d %d %d", &timeSlotID, &requestNum, &resourceNum);
    while (requestNum--) {
      fscanf(fin, "%d", &requestId);
      //printf("%d ",requestId);
      Request request(requestId);
      v_request.push_back(request);
    }
    //printf("\n");
    for(i=0;i<resourceNum;i++) {
      fscanf(fin, "%d", &resourceId);
      //printf("%d ",resourceId);
      Resource resource(resourceId);
      v_resource.push_back(resource);
    }
    //printf("\n");
    // input edges
    fscanf(fin, "%d", &edges);
    for(i=0;i<edges;i++) {
      fscanf(fin, "%d %d %d\n", &edgeId, &requestId, &resourceId);
      yn=v_resource[resourceId]->*v_request[requestId];
    }
    for(i=cnt;i<v_resource.size();i++){
      requestId=v_resource[i].assign(v_request);
      if(requestId!=-1){
        resourceId=v_resource[i].getId();
        v_request[requestId].assign(resourceId);
        satisfiedRequests=Request::getCounter();
      }
    }
    cnt+=resourceNum;
  }
  fprintf(fout,"%d\n",satisfiedRequests);
  for(i=0;i<v_request.size();i++){
    v_request[i].output(fout);
  }
  return 0;
}