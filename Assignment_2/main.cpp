#include "request.h"
#include "resource.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#define MAX_SIZE 1000
using namespace std;

int main(int argc,char *argv[]) {
  FILE *fin = fopen(argv[1], "r");
  FILE *fout=fopen("./result.txt","w");
  int timeSlots = 0, timeSlotID = 0, requestNum = 0, resourceNum = 0;
  int requestId = 0, resourceId = 0;
  int edges = 0, edgeId = 0;
  static int satisfiedRequests;
  int i = 0;
  vector<Request> v_request;
  vector<Resource> v_resource;
  bool yn, isAlloc;
  v_request.reserve(1010);
  v_resource.reserve(1010);

  // read request and resource
  fscanf(fin, "%d", &timeSlots);
  while (timeSlots--) {
    fscanf(fin, "%d %d %d", &timeSlotID, &requestNum, &resourceNum);
    while (requestNum--) {
      fscanf(fin, "%d", &requestId);
      Request request(requestId);
      v_request.push_back(request);
    }
    while (resourceNum--) {
      fscanf(fin, "%d", &resourceId);
      Resource resource(resourceId);
      v_resource.push_back(resource);
    }

    // input edges
    fscanf(fin, "%d", &edges);
    while (edges--) {
      fscanf(fin, "%d %d %d\n", &edgeId, &requestId, &resourceId);
      // find resource matching list
      yn = v_resource[resourceId]->*v_request[requestId];
      if (yn)
        v_resource[resourceId].doMatching(v_request[requestId]);
    }
    
    // match resource to request
    for (i = 0; i < v_resource.size(); i++) {
      yn = v_resource[i].checkMatched();
      if (!yn) {
        v_resource[i].doSorting();
        requestId = v_resource[i].allocateResource();
        if (requestId != -1) {
          v_request[requestId].matchResource(i);
        }
      }
    }
  }
  fclose(fin);

  for (i = 0; i < v_request.size(); i++){
    yn=v_request[i].checkMatched();
    if(yn) satisfiedRequests=Request::getCounter();
  }

    // print out result
  fprintf(fout,"%d\n", satisfiedRequests);
  for (i = 0; i < v_request.size(); i++)
    v_request[i].printResult(fout);
fclose(fout);
  return 0;
}