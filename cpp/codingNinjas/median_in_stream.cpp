#include <bits/stdc++.h>
using namespace std;

vector<int> findMedian(vector<int> &arr, int n){
	
	// Write your code here 
    vector<int> ans, temp;

    for (int i=0; i<n; i++)
    {
        temp.push_back(arr[i]);
        sort(temp.begin(), temp.end());
        if (i&1)
            ans.push_back((temp[i/2]+temp[i/2+1])/2);
        else
            ans.push_back(temp[i/2]);
    }

    for (int i=0; i<ans.size();  i++)
        cout << ans[i] << " ";

    return ans;
}

int main()
{
    vector<int> arr = {5,3,8};
    findMedian(arr, arr.size());
}
