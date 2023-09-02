#include <bits/stdc++.h>
using namespace std;

vector<int> findMedian(vector<int> &arr, int n){
	
	// Write your code here 
    priority_queue <int> l, r;
    arr.push_back(0);
    vector<int> ans;
    l.push(arr[0]);
    int median =arr[0];

    for (int i=1; i<=n; i++)
    {
        if (l.size()>r.size())
        {
            median =l.top();
            if (median<arr[i])
                r.push(-1 * arr[i]);
            else
                r.push(-1 * l.top()),
                l.pop(), l.push(arr[i]);
        }   
        else if (r.size()>l.size())
        {
            median = -1 * r.top();
            if (median<arr[i])
                l.push(-1 * r.top()),
                r.pop(), r.push(-1 *arr[i]);
            else
                l.push(arr[i]);
        }   
        else
        {
             median = (l.top() +(-1 * r.top()))/2;
             if (median<arr[i])
                 r.push(-1 * arr[i]);
             else 
                 l.push(arr[i]);
        }
        cout << median << endl;
        ans.push_back(median);
    }

    return ans;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	vector<int> temp= {2,3,4};
	findMedian(temp, temp.size());
}
