class Solution{
    public:
    int kthElement(int arr1[], int arr2[], int n, int m, int k)
    {
        
        int l1 =0, r1 =n-1;
        int l2 =0, r2 =m-1;

        while (true)
        {
            int m1 = l1 + (r1 -l1)/2;
            int m2 = l2 + (r2 -l2)/2;

            if (arr[m1] > arr[m2] && m1+m2+1 =k)
                return m1;
            else if (m1+m2 =k)
                return m2;

            if (l1<r1)
            {
                if (m1+m2 < k)
                    l1 =m1 +1;
                else 
                    r1 =m1 -1;
            }
            if (l2<r2)
            {
                if (m1+m2 < k)
                    l2 = m2 +1;
                else
                    r2 = m2 -1;
            }
        }
    }
};
