#include <cstdio>
#include <cstdlib>
#include <random>
#include "request.h"
using namespace std;


default_random_engine generator(1);
uniform_real_distribution<double> uniform(0.0,1.0);
int Request::counter=0;

// Constructor of Request
Request::Request(int id):id(id),bool(false)
{
    double w=uniform(generator);
    weight=w;
}

bool Request::checkMatched(){
    if(matched) return true;
    return false;
}

double Request::getWeight(){
    return weight;
}

int Request::getId(){
    return id;
}

