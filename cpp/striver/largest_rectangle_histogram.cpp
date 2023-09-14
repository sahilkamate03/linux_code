class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        vector<int> rtl(heights.size()),  ltr(heights.size());
        for (int i=heights.size()-1; i>=0; i--)
        {
            while(!st.empty() && heights[i] <= heights[st.top()])
                st.pop();

            if (st.empty())
                rtl[i] =-1;
            else
                rtl[i] =st.top();                
            
            st.push(i);
        }     

        for (auto &x : rtl)
            cout << x << " ";
        cout << endl;

        st = stack<int>();
        for (int i=0; i<heights.size(); i++)
        {
            while(!st.empty() && heights[i] <= heights[st.top()])
                st.pop();

            if (st.empty())
                ltr[i] =-1;
            else
                ltr[i] =st.top();                
            
            st.push(i);
        }

        for (auto &x : ltr)
            cout << x << " ";
        cout << endl;

        return -1;

    }
};