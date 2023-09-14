#include <bits/stdc++.h>
using namespace std;

int getR(int x)
{
    int l =0, r =32;
    int ans =0;
	while (l <= r) {
		int m = l + (r - l) / 2;

		if (pow(2,m) >= x+m+1)
			 ans =m;

		if (pow(2,m) < x+m+1)
			l = m + 1;

		else
			r = m - 1;
	}

	return ans;
}

int getRD(int x)
{
    int l =0, r =32;
    int ans =0;
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (pow(2,m) >= x)
             ans =m;

        if (pow(2,m) < x)
            l = m + 1;

        else
            r = m - 1;
    }

    return ans;
}

vector<int> encodeHamming(vector<int> data)
{
    vector<int> hC;
    int n =data.size();
    int r =getR(n);
    cout << r <<endl;

    int counter =0;
    int k= 0;
    for (int i=0; i<n+r; i++)
    {
        if (counter < r && i == pow(2,counter) -1)
        {
            hC.push_back(-1);
            counter++;
        } else{
            hC.push_back(data[n-k-1]);
            k++;
        }
    } 

    for (int i=0; i<r; i++)
    {
        int ans =0;
        for (int j=pow(2,i); j<=n+r; j++)
        {
            int x =j>>i;
            if (x&1 && hC[j-1]!=-1)
            {
                ans ^=hC[j-1];
            }
        }       
        hC[pow(2,i) -1] =ans;
    }       

    return hC;
}

void decodeHamming(vector<int> hc)
{
   vector<int> R;
   bool correct =true;
   int n =hc.size();
   int r =getRD(n); 

   for (int i=0; i<r; i++)
   {
    int ans =0;
    for (int j=pow(2,i); j<=hc.size(); j++)
    {
        int x =j>>i;
        if (x&1)
        {
            ans ^=hc[j-1];
            cout << j << endl;
            // cout << j-1 << " " << hc[j-1] << endl;
        }
    }

    cout << ans << "  " << hc[pow(2,i)-1] << endl;
    if (ans != hc[pow(2,i)-1])
        correct =false;
    R.push_back(ans);
   }

   cout << correct << endl;
}

int main()
{
    vector<int> data ={1,0,1,1,0,1,1,1};
    vector<int> hc =encodeHamming(data);
    for (auto x: hc)
    {
        cout << x << " ";
    }
    cout << endl;
    decodeHamming(hc);

}
