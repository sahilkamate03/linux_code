#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif
  int t;
  cin >> t;
  while (t--)
  {
    int n, c, k;
    cin >> n >> c;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
      int x;
      cin >> x;
      v.push_back(x);
    }

    int l = 0, r = 1e9;
    while (l <= r)
    {
      int s = 0;
      int m = l + (r - l) / 2;
      for (int i = 0; i < n; i++)
      {
        s += (v[i] + (2 * m)) * (v[i] + (2 * m)) ;
      }
      if (s == c)
        cout << m << endl;
      if (s < c)
        l = m + 1;
      else
        r = m - 1;
    }
  }
}