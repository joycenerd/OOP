#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "resource.h"
#include "request.h"
using namespace std;

using namespace std;

Resource::Resource(int id):id(id),matched(false){

}

bool cmp(matchList a,matchList b){
    double value_a=a.getWeight();
    double value_b=b.getWeight();
    return a>b;
}

bool operator ->*(const Resource &resource,const Request& request){
    bool isMatched=request.checkMatched();
    if(isMatched) return false;
    return true;
}

void Resource::doMatching(Request request){
    matchList.push_back(request);
}

bool Resource::checkMatched(){
    if(matched) return true;
    return false;
}

void Resource::doSorting(){
    sort(matchList.begin(),matchList.end(),cmp);
}

bool Resource::allocateResource(){
    bool isMatched;
    for(int i=0;i<matchList.size();i++){
        isMatched=matchList[i].checkMatched();
        if(isMatched) continue;
        matched=true;
        requestId=matchList[i].getId();
        return true;
    }
    return false;
}