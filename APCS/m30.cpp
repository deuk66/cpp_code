#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;
int main(){
    system("chcp 65001 >> nul");
    int n ;
    cin>>n;
    n++;
    vector <bool> v(n,true);
    for(auto&& b :v){
        b=true;
    }
    for(int i=2;i<sqrt(n);i++){
        if(v[i]){
            for(long long j=(long long)i*(long long)i;j<n;j+=i){
                if(j%i==0){
                    v[j]=0;
                }
            }
        }
    }
    v[0]=0;
    v[1]=0;
    cout<<"小於"<<n<<"的質數有:"<<endl<<"[";
    for(int i=1;i<n;i++){
        if(v[i]){
            cout<<i<<" ";
        }
    }
    int total=0;
    for(bool b:v){
        if(b){
            total++;
        }
    }
    cout<<'\b'<<"]"<<endl;
    cout<<"共"<<total<<"個"<<endl;
    return 0;
}