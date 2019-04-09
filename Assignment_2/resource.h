#ifndef RESOURCE_H
#define RESOURCE_H
#include "request.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Resource {

public:
  explicit Resource(int inputId);
  friend bool operator->*(Resource &resource, Request &request);
  //void doMatching(Request request);
  bool checkMatched();
  friend class Request;
  int assign(vector<Request> v_request);
  int getId(){return id;};

private:
  int id;
  bool matched;
  int requestId;
  int maxId;
  double maxWeight=-1;
  int rejectId=-1;
  vector<pair<int,int>> matchList;
};

#endif