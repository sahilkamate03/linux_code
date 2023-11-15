#include<bits/stdc++.h>
using namespace std;

void worker(vector<int>& a)
{
    int pt1 =0;
    for(int i=0; i<a.size(); i++)
    {
        if (a[pt1]==0 && a[i]!=0) swap(a[i],a[pt1]), pt1++;
        if(a[pt1]!=0) pt1++;
    }
}

int main()
{
	vector<int> a = {1,2,3,4,5,0,1,3,12};	
	worker(a);
    for (auto& x: a)
        cout << x << " ";
    cout << endl;
}
