#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;

typedef unsigned long int ui;

int main()
{
	int num;
	vector<pair<int,int> >v;
	int i;
	ui len;
	while(1){
		//scanf("%d",&num);
		cin >> num;
		if(num==-999) break;
		len=v.size();
		for(i=0;i<len;i++){
			if(v[i].first==num){
				int n=v[i].first;
				int freq=v[i].second;
				v.erase(v.begin()+i);
				v.push_back(make_pair(n,++freq));
				break;
			}
		}
		if(i==len) v.push_back(make_pair(num,1));
	}
	sort(v.begin(),v.end());
	len=v.size();
	for(i=len-1;i>=0;i--){
		//printf("%d %d\n",v[i].first,v[i].second);
		cout << v[i].first << " " << v[i].second << endl;
	}
	return 0;
}

// counting numbers
// count the number by one pass add it to a vector pair
// before outputting sort it by the number in descending order