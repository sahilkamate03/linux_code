#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int> &A, vector<int> &B, int C) {
    priority_queue<int> l, r;
    vector<int> ans;
    
    for (int i=0; i<A.size(); i++)
        l.push(A[i]), r.push(B[i]);
    
    int count =0;
    for (int i=0; i<C && count<C; i++)
    {
           ans.push_back(l.top() + r.top());
           count++;
           int le =l.top() ,re =r.top();
           l.pop(); r.pop();
           if (count < C)
            ans.push_back(max(l.top()+re, r.top()+le)),
            count++;
            if (count < C)
            ans.push_back(min(l.top()+re, r.top() +le)),
            count++;
    }
    
    for (int i=0; i<ans.size(); i++)
    	cout << ans[i] << " ";
    return ans;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	vector<int> A;
	vector<int> B;

	int n; cin>>n;
	for (int i=0; i<n; i++)
	{
		int x; cin >>x;
		A.push_back(x);
	}

	cin>>n;
	for (int i=0; i<n; i++)
	{
		int x; cin>> x;
		B.push_back(x);
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());


	int C; cin>>C;
	for (int i=0; i<A.size(); i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	for (int i=0; i<A.size(); i++)
	{
		cout << B[i] << " ";
	}
	cout << endl;
	solve(A, B, C);
}
