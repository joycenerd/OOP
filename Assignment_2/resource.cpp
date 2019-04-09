#include "resource.h"
#include "request.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

using namespace std;

// constructor: resourceId,not match
Resource::Resource(int inputId) : id(inputId), matched(false){}

// add request to matchlist if not assigned
bool operator ->*(Resource &resource, Request &request) { 
  bool isMatch=request.checkMatched();
  if(isMatch) return false;
  double weight=request.getWeight();
  int reqId=request.getId();
  resource.matchList.push_back(make_pair(reqId,weight));
  return true;
}
// check if resource is allocated
bool Resource::checkMatched() {
  if (matched)
    return true;
  return false;
}

// compare function of sorting matching list
bool cmpBySec(const pair<int,double> &a,const pair<int,double> &b){
  return a.second<b.second;
}

// match resource to request
int Resource::assign(vector<Request> v_request){
  sort(matchList.begin(),matchList.end(),cmpBySec);
  while(!matchList.empty()){
    int matchId=matchList.back().first;
    bool isMatch=v_request[matchId].checkMatched();
    if(isMatch) matchList.pop_back();
    else{
      requestId=matchId;
      matched=true;
      return requestId;
    }
  }
  return -1;
}
