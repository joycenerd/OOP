#ifndef REQUEST_H
#define REQUEST_H
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

class Request{
public:
  explicit Request(int inputId);
  double getRandom();
  bool checkMatched() const;
  double getWeight();
  int getId();
  static int getCounter();
  void reassign(){matched=false;};
  void matchResource(int resource);
  void printResult(FILE *fout);

private:
  int id;
  double weight;
  bool matched;
  int resourceId;
  static int counter;
};

#endif