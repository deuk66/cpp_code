#include <iostream>
#include <vector>
using namespace std;
int main(){
    int x=0,n=0;
    cin>>x;
    cin>>n;
    int phones[n];
    for(int i=0;i<n;i++){
        cin>>phones[i];
    }
    vector <int>s[x];
    int min=0;
    for(int i=0;i<x;i++){
        s[i].push_back(i);
    }
    for(int i=0;i<n;i++){
        min=999999999;
        for(int j=0;j<x;j++){
            if(j<min){
                min=j;
            }
        }
        s[min].push_back(i);
    }
    int total[x];
    int max=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<s[i].size();j++){
            total[i]+=phones[s[i][j]];
        }
    }
    for(int i=0;i<x;i++){
        if(total[i]>max){
            max=total[i];
        }
    }
    cout<<max<<endl;
    return 0;
}