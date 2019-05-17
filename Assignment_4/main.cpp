#include <iostream>
#include <cstdio>
using namespace std;


int main(int argc,char *argv[])
{
    int numOfNodes;
    double x,y;
    FILE *fin=fopen(argv[1],"r");
    fscanf(fin,"%d",&numOfNodes);
    printf("%d\n",numOfNodes);
    return 0;
}
