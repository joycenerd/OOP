#include <cstdio>
#include <iostream>
using namespace std;
#define N 5010


int main()
{
	int n;
	//scanf("%d\n",&n);
	cin >> n;
	int i;
	int num[N];
	for(i=0;i<n;i++)
		cin >> num[i]; 
	//scanf("%d",&num[i]);
	int j;
	int count=0;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(num[i]>2*num[j]) count++;
		}
	}
	//printf("%d\n",count);
	cout << count << endl;
	return 0;
}

// Significant inversions (easy)
// check every pair that meets i < j
// if ai > 2aj than pair add 1