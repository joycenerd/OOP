#ifndef RESOURCE_H
#define RESOURCE_H
#include "request.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class Resource {

public:
  explicit Resource(int inputId);
  friend bool operator->*(const Resource &resource, const Request &request);
  void doMatching(Request request);
  bool checkMatched();
  void doSorting();
  int allocateResource();
  friend class Request;

private:
  int id;
  bool matched;
  int requestId;
  vector<Request> matchList;
};

#endif