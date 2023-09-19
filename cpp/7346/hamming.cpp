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

    int counter =r-1;
    int k= 0;
    for (int i=data.size()+r-1; i>=0; i--)
    {
        if (counter >= 0 && i == pow(2,counter) -1)
        {
            hC.push_back(-1);
            counter--;
        } else{
            hC.push_back(data[k]);
            k++;
        }
    } 
    hC.push_back(-1);
    reverse(hC.begin(), hC.end());

    for (int i=0; i<r; i++)
    {
        int ans =0;
        for (int j=1; j<=n+r; j++)
        {
            int x =j>>i;
            if (x&1 && hC[j]!=-1)
                ans ^=hC[j];
        }       
        hC[pow(2,i)] =ans;
    }       
    return hC;
}

vector<int> decodeHamming(vector<int> &hc)
{
   vector<int> R;
   bool correct =true;
   int n =hc.size();
   int r =getRD(n); 
   vector<int> data;
   for (int i=0; i<r; i++)
   {
    int ans =0;
    for (int j=1; j<=hc.size(); j++)
    {
        int x =j>>i;
        if (x&1)
            ans ^=hc[j];
    }

    if (ans != 0)
        correct =false;
    R.push_back(ans);
   }

   if (!correct)
   {
        int t =0;
        for (int i=0; i<r; i++)
            if(R[i])
                t+=pow(2,int(i));
        
        if (hc[t]==0)
            hc[t]=1;
        else 
            hc[t]=0;
   }

   int k =0;
    for (int i=1; i<=hc.size()-1; i++)
    {
        if (i!=pow(2,k))
        {
            data.push_back(hc[i]); 
        } else
            k++;
    }

   return data;
}

int main()
{
    vector<int> data ={1,0,1,1,0,1,1,0};
    vector<int> hc =encodeHamming(data);
    hc[2] =1;
    vector<int> output =decodeHamming(hc);
    for (auto &x: output)
        cout << x;
    cout << endl;
}
