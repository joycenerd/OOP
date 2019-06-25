#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define N 1010
using namespace std;
typedef unsigned long int ui;

int main()
{
	char str[N];
	//fgets(str,N,stdin);
	cin >> str;
	ui len=strlen(str);
	for(int i=0;i<len;i++){
		int num=(int)str[i];
		num-=3;
		char temp=(char)num;
		//printf("%c",temp);
		cout << temp;
	}
	//printf("\n");
	cout << endl;
	return 0;
}

// Codec (easy)
// get the ascii code of the alphabet and minus 3 and turn it back to alphabet