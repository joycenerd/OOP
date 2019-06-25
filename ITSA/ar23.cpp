#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <istream>
#include <string>
#define N 1010
using namespace std;
typedef unsigned long int ui;


int main()
{
	//char line[N];
	string line;
	//fgets(line, N,stdin);
	getline(cin,line);
	//cout << line  << endl;
	ui len=line.length();
	int i,asc;
	for(i=0;i<len;i++){
		if(isupper(line[i])){
			if(line[i]<'N'){
				asc=line[i]-'A';
				//printf("%c",'N'+asc);
				cout << (char)('N'+asc);
			}
			else{
				asc=line[i]-'N';
				//printf("%c",'A'+asc);
				cout << (char)('A'+asc);
			}
		}
		else if(islower(line[i])){
			if(line[i]<'n'){
				asc=line[i]-'a';
				//printf("%c",'n'+asc);
				cout << (char)('n' + asc);
			}
			else{
				asc=line[i]-'n';
				//printf("%c",'a'+asc);
				cout << (char)('a'+asc);
			}
		}
		//else printf("%c",line[i]);
		else cout << line[i];
	}
	//printf("\n");
	cout << endl;
	return 0;
}

// An easy encoder (easy)
// map the ascii following the rules as the problem specify