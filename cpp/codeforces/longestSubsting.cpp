#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s) {
        int max = 0;
        set<char> set;
        for (int i = 0; i<s.length() ; i++){
            auto pos = set.find(s[i]);
            if(pos !=set.end()){
                if (max < set.size()){
                    max = set.size();
                }
            }
            set.insert(s[i]);
        }
        return max;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}
