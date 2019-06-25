#include <cstdio>
#include <iostream>
using namespace std;
#define N 70010


int main()
{
	int n,i;
	int arr[N]={0};
	//scanf("%d",&n);
	cin >> n;
	int num;
	for(i=0;i<n-1;i++){
		//scanf("%d",&num);
		cin >> num;
		arr[num]=1;
	}
	for(i=1;i<=n;i++){
		if(arr[i]==0){
			//printf("%d\n",i);
			cout << i <<endl;
			return 0;
		}
	}
}

// Who is missing? (easy)
// set a large array initialize to 0
// if the number has appear then set it to 1
// trace the array again if there is a 0 output the corresponding index