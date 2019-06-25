#include <cstdio>
#include <iostream>
using namespace std;
#define N 1010;


int main()
{
	int m,n;
	//scanf("%d%d",&m,&n);
	cin >> m >> n;
	int a;
	int count[2]={0};
	int i;
	while(m--){
		for(i=0;i<n;i++){
			//scanf("%d",&a);
			cin >> a;
			count[a]++;
		}
	}
	/*if(count[0]>count[1]) printf("0\n");
	else if(count[0]<count[1]) printf("1\n");
	else printf("2\n");*/
	if(count[0]>count[1]) cout << 0 << endl;
	else if(count[0]<count[1]) cout << 1 << endl;
	else cout << 2 << endl;
	return 0;
}

// Which one is more? (easy)
// count sum up all the 0 and 1 to compare which one has more