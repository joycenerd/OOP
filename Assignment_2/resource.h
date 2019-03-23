#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "request.h"
using namespace std;


class Resource{
    public:
        Resource(int inputID);
        friend bool operator ->*(const Resource& resource,const Request& request);
        void doMatching(Request request);
        bool checkMatched();
        void doSorting();
        void allocateResource();

    private:
        int id;
        bool matched;
        int requestId;
        vector<Request> matchList;
};