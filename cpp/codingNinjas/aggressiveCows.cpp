bool solve(vector<int> &stalls, int k, int m)
{
    int count =1; int prev =stalls[0];
    for (int i=1; i<stalls.size() && count<k; i++)
    {
        if (stalls[i] -prev >= m)
        {
            count++;
            prev =stalls[i];
        }
    }
    if (count == k) return true;
    return false;
}

int aggressiveCows(vector<int> &stalls, int k)
{
    //    Write your code here.
    sort(stalls.begin(), stalls.end());
    int s =0, e =stalls[stalls.size()-1] -stalls[0];
    int ans =0;
    while (s<=e)
    {
        int m =s +(e-s)/2;
        if (solve(stalls, k , m)) {
            ans = max(ans, m);
            s = m + 1;
        } else
            e =m-1;
    }
    return ans;
}
