#ifndef GFG_H
#define GFG_H
#include "fr.h"
#include <vector>
using namespace std;


// wait to complete Greedy part of routing
class GFG: public FR{
    public:
        GFG(){}
        GFG(int inId,double inX,double inY):FR(inId,inX,inY){}
        void getNextHop(vector<GFG> &v_nodes);
        void send(vector<GFG> &v_nodes);
    private:
        vector<GFG> gfg_nodes;
};

#endif