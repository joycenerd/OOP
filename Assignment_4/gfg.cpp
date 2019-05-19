#include "gfg.h"
#include "gfgpacket.h"
using namespace std;


// upcast the calling object type to GFG but other reamins FR to finish greedy part
void GFG::getNextHop(vector<FR> &v_nodes){
    int mode,i,vsize,nearest;
    double curDist,nxtDist;
    const int MAX_DIST=1000;
    GFGpacket packet=q_pkt.front();
    mode=packet.getMode();
    curDist=sqrt(pow(dstX-x,2)+pow(dstY-y,2));
    vsize=beforeNeighbor.size();
    nearest=-1;
    for(i=0;i<vsize;i++){
        nxtDist=sqrt(pow(dstX-beforeNeighbor[i].x,2)+pow(dstY-beforeNeighbor[i].y,2));
        if(nxtDist<curDist){
            curDist=nxtDist;
            nearest=beforeNeighbor[i].id;
        }
    }
    vector<FR> fr_nodes;
    for(i=0;i<v_nodes.size();i++){
        FR node=(FR) v_nodes[i];
        fr_nodes.push_back(node);
    }
    if(nearest==-1) FR::getNextHop(fr_nodes);
}