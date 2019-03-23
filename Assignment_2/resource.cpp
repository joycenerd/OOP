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

bool operator ->*(const Resource&,const Request& request){
    if(request.matched==false)
        return true;
}