#include <cstdio>
#include <cstring>
#include <iostream>
#define N 200
using namespace std;
typedef unsigned long int ui;

int main(){
	char line[N];
	int m[N],n[N];
	int t;
	fgets(line,N,stdin);
	sscanf(line,"%d",&t);
	//cout << t;
	int i;
	char *token[2];
	while(t--){
		fgets(line,N,stdin);
		token[0]=strtok(line," \0");
		token[1]=strtok(NULL," \0");
		ui lenm=strlen(token[0]);
		ui lenn=strlen(token[1])-1;
		//printf("%d %d\n",lenm,lenn);
		if(lenm==lenn){
			for(i=0;i<lenm;i++) m[i]=token[0][i]-'0';
			for(i=0;i<lenn;i++) n[i]=token[1][i]-'0';
			for(i=0;i<lenm;i++) cout << m[i] << n[i];
				//printf("%d%d",m[i],n[i]);
		}
		else if(lenm>lenn){
			for(i=0;i<lenm;i++) m[i]=token[0][i]-'0';
			int zero=lenm-lenn;
			for(i=0;i<zero;i++) n[i]=0;
			for(i=0;i<lenn;i++) n[i+zero]=token[1][i]-'0';
			for(i=0;i<lenm;i++) cout << m[i] << n[i];
				//printf("%d%d",m[i],n[i]);
		}
		else{
			for(i=0;i<lenn;i++) n[i]=token[1][i]-'0';
			int zero=lenn-lenm;
			for(i=0;i<zero;i++) m[i]=0;
			for(i=0;i<lenm;i++) m[i+zero]=token[0][i]-'0';
			for(i=0;i<zero-1;i++) cout << n[i] << m[i];
				//printf("%d%d",n[i],m[i]);
			//printf("%d",n[zero-1]);
			cout << n[zero-1];
			for(i=zero;i<lenn;i++) cout << m[i] << n[i];
				//printf("%d%d",m[i],n[i]);
		}
		//printf("\n");
		cout << endl;
	}
	return 0;
}

// |N^2|=|N| (easy)
// first check the length of two numbers are the same
// if not put 0 in  front of the shortest length number until the two number has the same length
// choose one digit from the first number and the other from the second number alternately
// until all the digit has been chosen 