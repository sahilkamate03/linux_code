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
		int n; cin >>n;
		map<int, int> up, side, nslope, pslope;
		for (int i=0; i<n; i++)
		{
			int x, y;
			cin >> x >> y;
			up[y]++; side[x]++;
			pslope[x+y]++; nslope[x-y]++;
		}

		int ans =0;

		for (auto x: up)
			ans += (x.second) * (x.second -1);

		for (auto x: side)
			ans += (x.second) * (x.second -1);
	
		for (auto x: pslope)
			ans += (x.second) * (x.second -1);

		for (auto x: nslope)
			ans += (x.second) * (x.second -1);	

		cout << ans << endl;
	}
}
