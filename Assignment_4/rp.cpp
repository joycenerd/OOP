#include "rp.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define MAX_SLOPE 100000
using namespace std;

void RP::planarize() {
  int vsize, i, j, yn;
  double midX, midY, radius, distance;
  vsize = beforeNeighbor.size();
  for (i = 0; i < vsize; i++) {
    midX = (this->x + beforeNeighbor[i].x) / 2;
    midY = (this->y + beforeNeighbor[i].y) / 2;
    radius = sqrt(pow(midX - this->x, 2) + pow(midY - this->y, 2));
    yn = 1;
    for (j = 0; j < vsize; j++) {
      if (j == i)
        continue;
      distance = sqrt(pow(midX - beforeNeighbor[j].x, 2) +
                      pow(midY - beforeNeighbor[j].y, 2));
      if (distance < radius) {
        yn = 0;
        break;
      }
    }
    if (yn)
      planarGraph.push_back(beforeNeighbor[i]);
  }
}

void RP::printNeighbor() {
  int vsize = 0, i;
  vsize = planarGraph.size();
  printf("[%d] ", id);
  for (i = 0; i < vsize; i++) {
    printf("%d ", planarGraph[i].id);
  }
  printf("\n");
}

void RP::addDst(int inDstId,double inDstX,double inDstY){
    dstId=inDstId;
    dstX=inDstX;
    dstY=inDstY;
}