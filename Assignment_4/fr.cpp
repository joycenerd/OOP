#include "fr.h"
using namespace std;

void FR::addDst(int inDstId,double inDstX,double inDstY){
    dstId=inDstId;
    dstX=inDstX;
    dstY=inDstY;
}

int FR::checkQueue(){
  GFGpacket packet;
  int nextId;
  if(q_pkt.empty())
    return -1;
  packet=q_pkt.front();
  nextId=packet.getNxtId();
  if(nextId==id)
    return id;
  q_pkt.pop();
  return -1;
}

void FR::planarize() {
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

void FR::printNeighbor() {
  int vsize = 0, i;
  vsize = planarGraph.size();
  printf("[%d] ", this->id);
  for (i = 0; i < vsize; i++) {
    printf("%d ", planarGraph[i].id);
  }
  printf("\n");
}