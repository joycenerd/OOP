#include <cstdio>
#include <cstring>
#include <iostream>
#define N 1010
using namespace std;
typedef unsigned long int ui;

int main()
{
	int t,n;
	char line[N];
	int arr1[N],arr2[N];
	//fgets(line,N,stdin);
	//sscanf(line,"%d",&t);
	cin >> t;
	while(t--){
		int ans[N]={0};
		//fgets(line,N,stdin);
		//sscanf(line,"%d",&n);
		cin >> n;
		//fgets(line,N,stdin);
		cin >> line;
		int i;
		for(i=0;i<n;i++) arr1[i]=line[n-i-1]-'0';
		//fgets(line,N,stdin);
		cin >> line;
		for(i=0;i<n;i++) arr2[i]=line[n-i-1]-'0';
		int j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				ans[i+j]+=arr1[i]*arr2[j];
				ans[i+j+1]+=ans[i+j]/10;
				ans[i+j]%=10;
			}
		}
		int start;
		for(i=N-1;i>=0;i--){
			if(ans[i]){
				start=i;
				break;
				} 
		}
		// for(i=start;i>=0;i--) printf("%d",ans[i]);
		for(i=start;i>=0;i--) cout << ans[i];
		cout << endl;	
	}
	return 0;
}

// Multiplication of Two Large Integers (medium)
// reverse the two numbers so it can aligned by MSB
// do multiplication and accumulator at the same time of one bit at a time
// output the answer in reverse order again