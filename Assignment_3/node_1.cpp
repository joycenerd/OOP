#include "node.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

void Node::printNeighbor() {
  int vsize = 0, i;
  vsize = planarGraph.size();
  printf("[%d] ", id);
  for (i = 0; i < vsize; i++) {
    printf("%d ", planarGraph[i].id);
  }
  printf("\n");
}

void Node::printBeforeNeighbor() {
  int vsize = 0, i;
  vsize = beforeNeighbor.size();
  printf("[%d] ", id);
  for (i = 0; i < vsize; i++) {
    printf("%d ", beforeNeighbor[i].id);
  }
  printf("\n");
}

void Node::planarize() {
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

void Node::addDst(int inDstId, double inDstX, double inDstY) {
  dstId = inDstId;
  dstX = inDstX;
  dstY = inDstY;
}

// if queue isn't empty and also nextID is me
int Node::checkQueue() {
  Packet packet;
  int nextId;
  if (q_pkt.empty())
    return -1;
  packet = q_pkt.front();
  nextId = packet.getNxtId();
  if (nextId == id) {
    return id;
  }
  q_pkt.pop();
  return -1;
}

double arcCos(double curX, double curY, double prevX, double prevY, double nxtX,
              double nxtY) {
  double aX, aY, bX, bY, aAbs, bAbs, degree;
  aX = prevX - curX;
  aY = prevY - curY;
  bX = nxtX - curX;
  bY = nxtY - curY;
  aAbs = sqrt(aX * aX + aY * aY);
  bAbs = sqrt(bX * bX + bY * bY);
  degree = acos((aX * bX + aY * bY) / (aAbs * bAbs));
  return degree;
}

bool sortBySec(const pair<int, double> &a, const pair<int, double> &b) {
  return a.second < b.second;
}
// calculate slope of the given line by coordinates
double lineFunc(Node node, double lastX, double lastY) {
  double curX, curY;
  curX = node.getX();
  curY = node.getY();
  double slope;
  slope = (lastY - curY) / (lastX - curX);
  return slope;
}

/*void getNewItx(double slope1, double x1, double y1, double slope2, double x2,
               double y2, double &newItxX, double &newitxY) {
  newItxX = (-slope2 * x2 + y2 + slope1 * x1 - y1) / (slope1 - slope2);
  newitxY = slope1 * (newItxX - x1) + y1;
  // printf("%f %f\n",newItxX,newitxY);
}*/

void Node::getNextHop(vector<Node> &v_nodes) {
  double itxX, itxY, degree, nxtX, nxtY, slope, side, dir, curSide,
      nxtSide, sdSlope;
  double crossing, curDegree,lastX,lastY,newItxX,newItxY;
  int i, vsize, srcId, nxtId,lastId;
  vector<pair<int, double>> angle;
  Packet packet = q_pkt.front();
  itxX = packet.getItxX();
  itxY = packet.getItxY();
  vsize = planarGraph.size();
  angle.clear();

  // case 1 current node is intersection point
  if (x == itxX && y == itxY) {
    slope = lineFunc(*this, dstX, dstY);
    dir = dstX - x;
    for (i = 0; i < vsize; i++) {
      nxtX = planarGraph[i].x;
      nxtY = planarGraph[i].y;
      degree = arcCos(x, y, dstX, dstY, nxtX, nxtY);
      side = slope * (nxtX - x) - (nxtY - y);
      if (packet.getLastId() == planarGraph[i].id)
        degree = 2 * M_PI;
      else if (dir > 0) {
        if (side < 0)
          degree = 2 * M_PI - degree;
      } 
      else if (dir <= 0) {
        if (side > 0)
          degree = 2 * M_PI - degree;
      }
      angle.push_back(make_pair(planarGraph[i].id, degree));
    }
    sort(angle.begin(), angle.end(), sortBySec);
    packet.modifyInfo(id, angle[0].first);
    q_pkt.pop();
    q_pkt.push(packet);
    printf("itxX=%f,itxY=%f\n",itxX,itxY);
    return;
  }

  // find next node with smallest angle from current node
  srcId = packet.getSrcId();
  sdSlope = lineFunc(v_nodes[srcId], dstX, dstY);
  lastId=packet.getLastId();
  lastX=v_nodes[lastId].x;
  lastY=v_nodes[lastId].y;
  while (1) {
      printf("itxX=%f,itxY=%f\n",itxX,itxY);
    slope = lineFunc(*this, lastX, lastY);
    for (i = 0; i < vsize; i++) {
      nxtX = planarGraph[i].x;
      nxtY = planarGraph[i].y;
      degree = arcCos(x, y, lastX, lastY, nxtX, nxtY);
      side = slope * (nxtX - x) - (nxtY - y);
      dir = lastX - x;
      if (lastId == planarGraph[i].id)
        degree = 2 * M_PI;
      else if (dir >= 0) {
        if (side < 0)
          degree = 2 * M_PI - degree;
      } 
      else if (dir < 0) {
        if (side > 0)
          degree = 2 * M_PI - degree;
      }
      angle.push_back(make_pair(planarGraph[i].id, degree));
    }
    sort(angle.begin(), angle.end(), sortBySec);
    printf("%d\n",id);
    for(i=0;i<angle.size();i++) printf("%d %f\n",angle[i].first,angle[i].second);
    nxtId = angle[0].first;
    nxtX = v_nodes[nxtId].x;
    nxtY = v_nodes[nxtId].y;
    curSide = sdSlope * (x - dstX) - (y - dstY);
    nxtSide = sdSlope * (nxtX - dstX) - (nxtY - dstY);
    crossing = curSide * nxtSide;

    // case2: next node won't cross source destination line
    if (crossing >= 0) {
      packet.modifyInfo(id, nxtId);
      q_pkt.pop();
      q_pkt.push(packet);
      printf("case2\n");
      return;
    }

    // if next node cross the source destination line
    // find new intersection point
    slope = lineFunc(*this,nxtX,nxtY);
    itxX = (-slope * x + y + sdSlope * dstX - dstY) / (sdSlope - slope);
    itxY = sdSlope * (itxX - dstX) + dstY;
    dir=dstX-itxX;

    // case3: if the intersection point has seen before cross the line
    if((dir>=0 && itxX<=packet.getItxX()) || (dir<=0 && itxX>=packet.getItxX())){
        packet.modifyInfo(id, nxtId);
        q_pkt.pop();
        q_pkt.push(packet);
        printf("case3\n");
        printf("%f %f\n",itxX,packet.getItxX());
        printf("%f\n",dir);
        return;
    }

    degree = arcCos(itxX, itxY, dstX, dstY, x, y);
    side = sdSlope * (x - itxX) - (y - itxY);
    packet.updateItx(itxX, itxY);

    // case4: if calculate angle from intersection point can cross the line than cross the line
    if (dir >= 0) {
      if (side < 0)
        degree = 2 * M_PI - degree;
    } 
    else if (dir < 0) {
      if (side > 0)
        degree = 2 * M_PI - degree;
    }
    curDegree = degree;

    degree = arcCos(itxX, itxY, dstX, dstY, nxtX, nxtY);
    side = sdSlope * (nxtX - itxX) - (nxtY - itxY);
    if (dir >= 0) {
      if (side < 0)
        degree = 2 * M_PI - degree;
    } 
    else if (dir < 0) {
      if (side > 0)
        degree = 2 * M_PI - degree;
    }

    if (degree <= curDegree) {
      packet.modifyInfo(id, nxtId);
      q_pkt.pop();
      q_pkt.push(packet);
      printf("case4");
      return;
    }
    // case5: if stay at current node than use itersection point as last node and calculate again
    lastX=itxX;
    lastY=itxY;
    lastId=nxtId;
    angle.clear();
    printf("case5\n");
  }
}

// send packet
void Node::send(vector<Node> &v_nodes) {
  int vsize, i, neighborId;
  Packet packet;
  vsize = beforeNeighbor.size();
  packet = v_nodes[id].q_pkt.front();
  // printf("%d ",packet.getLastId());
  v_nodes[id].q_pkt.pop();
  for (i = 0; i < vsize; i++) {
    neighborId = beforeNeighbor[i].getId();
    v_nodes[neighborId].q_pkt.push(packet);
  }
}