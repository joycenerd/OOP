#include <cstdio>
#include <cstring>
#include <iostream>
#define N 1010
using namespace std;
typedef unsigned long int ui;

int main()
{
	char str[N],rev[N];
	//fgets(str,N,stdin);
	cin >> str;
	ui len=strlen(str);
	int i;
	int flag=0;
	for(i=0;i<len;i++) rev[i]=str[len-i-1];
	for(i=0;i<len;i++){
		if(str[i]!=rev[i]) break;
	}
	//if(i==len) printf("yes\n");
	//else printf("no\n");
	//printf("%d\n",i);
	if(i==len) cout << "yes" << endl;
	else cout << "no" << endl;
	return 0;
}

// Palindorme (medium)
// reverse the original string and store it in another string
// if the two strings are the same, print yes, else print no