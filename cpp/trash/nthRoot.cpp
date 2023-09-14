#include<bits/stdc++.h>
using namespace std;
string xorr(string a,string b){
    string ans = "";
    for(int i = 0;i<a.size();i++){
        if(a[i]!=b[i])ans+='1';
        else ans+='0';
    }
    string rem = "";
    int i=0;
    while(i<a.size() and ans[i]=='0'){
        i++;
    }
    for(int j = i;j<a.size();j++)rem+=ans[j];
    return rem;
}
string remainder(string data,string key){
    string rem = "";
    int k = key.size(),n = data.size();
    for(int i = 0;i<k-1;i++){
        rem+=data[i];
    }
    for(int i = k-1;i<n;i++){
        rem+=data[i];
        rem = xorr(rem,key);
        while(i<n-1 and rem.size()<k-1)rem+=data[++i];
        cout<<rem<<endl;
    }
    string final = "";
    for(int i = 0;i<k-rem.size();i++)final+='0';
    final+=rem;
    return final;
}
int main(){
    string data = "100100000";
    string key = "1101";
    string rem = remainder(data,key);
    cout<<rem<<endl;
    string datasend = data+rem;
}