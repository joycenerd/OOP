#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;


int main()
{
	int t,n,num;
	//scanf("%d",&t);
	cin >> t;
	while(t--){
		int maxi=0;
		int total=0;
		//scanf("%d",&n);
		cin >> n;
		while(n--){
			//scanf("%d",&num);
			cin >> num;
			total+=num;
			if(total>0) maxi=max(total,maxi);
			else total=0;
		}
		//printf("%d\n",maxi);
		cout << maxi << endl;
	}
	return 0;
}

// Finding a Maximum Profit Interval for a Long Term Investment (medium)
// start from the first element, if larger than 0 than add to the profit
// if larger than current maximum set it as maximum
// if smaller than 0 set the profit to 0 and add on from that point
