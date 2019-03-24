#include "request.h"
#include <cstdio>
#include <cstdlib>
#include <random>
using namespace std;

int Request::counter = 0;
default_random_engine generator(2);
uniform_real_distribution<double> uniform(0.0, 1.0);

// Constructor of Request
Request::Request(int inputId) : id(inputId), matched(false) {
  double w = uniform(generator);
  //printf("%f ",w);
  weight = w;
}

// if request is matched
bool Request::checkMatched() const{
  if (matched)
    return true;
  return false;
}

// get the weight of the request
double Request::getWeight() { return weight; }

// get requestId
int Request::getId() { return id; }

// count satisfied request
int Request::getCounter() {
  counter++;
  return counter;
}

// assigned resource to request
void Request::matchResource(int resource) {
  matched = true;
  resourceId = resource;
}

// print satisfied resourceId and requestId
void Request::printResult() {
  if (matched)
    printf("%d %d\n", id, resourceId);
}