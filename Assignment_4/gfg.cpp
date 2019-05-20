#include "gfg.h"
#include "gfgpacket.h"
using namespace std;

// upcast the calling object type to GFG but other reamins FR to finish greedy
// part
void GFG::getNextHop(vector<GFG> &v_nodes) {
  int mode, i, vsize, nearest;
  double curDist, nxtDist,mini;
  const int MAX_DIST = 1000;
  GFGpacket packet = q_pkt.front();
  mode = packet.getMode();
  mini=packet.getDist();
  printf("mini=%f\n",mini);
  if(mode==1){
    curDist = sqrt(pow(dstX - x, 2) + pow(dstY - y, 2));
    if(curDist>=mini){
        vector<FR> fr_nodes;
        printf("%f Face\n",mini);
        for (i = 0; i < v_nodes.size(); i++) {
            FR node = (FR)v_nodes[i];
            fr_nodes.push_back(node);
        }
        packet.rstSrcId(id);
        q_pkt.pop();
        q_pkt.push(packet);
        FR::getNextHop(fr_nodes);
        return;
    }
  }
  vsize = beforeNeighbor.size();
  nearest = -1;
  for (i = 0; i < vsize; i++) {
    /*if(beforeNeighbor[i].id==dstId){
      nearest=dstId;
      mini=0;
      break;
    }*/
    nxtDist = sqrt(pow(dstX - beforeNeighbor[i].x, 2) +
                   pow(dstY - beforeNeighbor[i].y, 2));
    if (nxtDist < mini) {
      printf("%d %d %f\n",id,beforeNeighbor[i].id,nxtDist);
      mini = nxtDist;
      nearest = beforeNeighbor[i].id;
    }
  }
  // printf("%d\n",nearest);
  if (nearest != -1) {
    packet.modifyInfo(id, nearest);
    packet.rstDist(mini);
    packet.setmod(0);
    q_pkt.pop();
    q_pkt.push(packet);
    printf("%f Greedy\n",mini);
    return;
  }
  vector<FR> fr_nodes;
  if(mode==1) printf("%f Face\n",mini);
  else printf("%f Greedy to face\n",mini);
  for (i = 0; i < v_nodes.size(); i++) {
    FR node = (FR)v_nodes[i];
    fr_nodes.push_back(node);
  }
  packet.rstSrcId(id);
  packet.setmod(1);
  q_pkt.pop();
  q_pkt.push(packet);
  FR::getNextHop(fr_nodes);
}

// send packet
void GFG::send(vector<GFG> &v_nodes) {
  int vsize, i, neighborId;
  GFGpacket packet;
  vsize = beforeNeighbor.size();
  packet = v_nodes[id].q_pkt.front();
  v_nodes[id].q_pkt.pop();
  for (i = 0; i < vsize; i++) {
    neighborId = beforeNeighbor[i].getId();
    v_nodes[neighborId].q_pkt.push(packet);
  }
}