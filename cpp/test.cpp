#include<bits/stdc++.h>
using namespace std;

class student{
    int age;
    string name;
    public:
    student(){
        int age = 0;
        string name = "";
    }
    void setName(string name){
        this->name = name;
    }
    void setAge(int age){
        this->age = age;
    }
    void print(){
        cout<<"Name is :"<<this->name<<"   ";
        cout<<"Age is :"<<this->age<<endl;
    }
};

int main(){
    student s1;
    s1.setAge(20);
    s1.setName("Ajay");
    student s2(s1);
    s1.print();
    cout<<endl;
    s2.print();
    cout<<endl;
    s2.setName("Abhay");
    s2.setAge(40);
    s1.print();
    cout<<endl;
    s2.print();
    cout<<endl;
}
