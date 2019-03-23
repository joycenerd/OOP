#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

class Request {
public:
  Request(int inputId);

private:
    int id;
    double weight;
    bool matched;
    int resourceId;
}