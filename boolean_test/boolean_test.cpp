#include <cmath>
#include<iostream>
#include <string>
using namespace std;
int main(){
    int n=0;
    cout<<"input variable number:"<<endl;
    cin>>n;
    bool b[n]={};
    // for(int i=0;i<n;i++){
    //     cout<<"input "<<'A'<<" :"<<endl;
    //     cin>>b[i];
    // }
    int pow_=int(pow(2,n));
    bool c[pow_]={};
    bool d[pow_]={};
    for(int i =0;i<pow_;i++){
        c[i]=(!b[2])&&(b[0]||b[1]);
        d[i]=(!b[2])||(b[0]&&b[1]);
        b[2]=!b[2];
        if(i+1%2==0){
            b[1]=!b[1];
        }
        if(i+1%4==0){
            b[0]=!b[0];
        }
    }
    bool same=1;
    for(int i =0;i<pow_;i++){
        if(c[i]!=d[i]){
            same=0;
        }
    }
    cout<<same;
    // cout<<"input boolean symbol:"<<endl;
    // string s="";
    
    return 0;
}