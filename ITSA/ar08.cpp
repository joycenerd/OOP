
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <iostream>
#define N 1010
using namespace std;
typedef unsigned long int ui;

int main(){
	char line[N];
	fgets(line,N,stdin);
	ui len=strlen(line)-1;
	int sum=0;
	int maxi=0;
	for(int i=0;i<len;i++){
		if(isdigit(line[i])){
			if(i-1>=0 && line[i-1]=='-')sum-=line[i]-'0';
			else sum+=line[i]-'0';
			if(sum>0){
				maxi=max(sum,maxi);
			}
			else sum=0;
		}
	}
	//printf("%d\n",maxi);
	cout << maxi << endl;
	
}

// maximum consecutive sum
// choose the number as long as adding it larger than 0 and compare and set the maximum