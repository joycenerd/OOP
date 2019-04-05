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
Resource::Resource(int inputId) : id(inputId), matched(false) {}

// check is request is assigned or not
bool operator ->*(const Resource &resource, const Request &request) {
  bool isMatched = request.checkMatched();
  if (isMatched)
    return false;
  return true;
}

// add request into matching list
void Resource::doMatching(Request request) { matchList.push_back(request); }

// check if resource is allocated
bool Resource::checkMatched() {
  if (matched)
    return true;
  return false;
}

// sort request in resource matching list by its weight
bool cmp(Request& a, Request& b) {
  double value_a = a.getWeight();
  double value_b = b.getWeight();
  return value_a > value_b;
}

void Resource::doSorting() { 
    sort(matchList.begin(), matchList.end(), cmp);
}

// assigned request to resource
int Resource::allocateResource() {
  bool isMatched;
  for (int i = 0; i < matchList.size(); i++) {
    isMatched = matchList[i].checkMatched();
    if (isMatched) return -1;
    matched = true;
    requestId = matchList[i].getId();
    return requestId;
  }
  return -1;
}