#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int t; cin >>t;
	while (t--)
	{
		int i =0;
		int n; cin>>n;
		int ans =0;
		bool go =false;

		for (int i=0; i<n; i++)
		{
			int x; cin>>x;
			if (x!=0 && !go && i!=n-1)
			{
				go =true;
				ans =x;
			}
			else if (x!=0 && go && i!=n-1)
			{
				ans +=x;
			}
			else if (x==0 && go && i!=n-1)
				ans++;
		}
		cout << ans << endl;
	}
}
