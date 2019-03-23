#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

class Request {
public:
  Request(int inputId);
  bool checkMatched();
  double getWeight();
  int getId();
  static int getCounter();
  void matchResource();

private:
    int id;
    double weight;
    bool matched;
    int resourceId;
    static int counter;
};
