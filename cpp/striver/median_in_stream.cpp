vector<int> findMedian(vector<int> &arr, int n){
	
	// Write your code here 
    priority_queue <int> l, r;
    vector<int> ans;
    l.push(arr[0]);
    int medina =arr[0];
    for (int i=1; i<n; i++)
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
             if (medain<arr[i])
                 r.push(-1 * arr[i]);
             else 
                 l.push(arr[i]);
        }

        ans.push_back(median);
    }
}


