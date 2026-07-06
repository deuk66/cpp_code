#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;

int abs(int a){
    return (a>=0)?(a):(-a);
}
int main (){
    int m,n,x;
    cin>>n>>m;
    vector <int> v(n);
    for(int &i:v){
        int a;
        cin>>a;
        i=a;
        int l=&i-v.data();
        cout<<"set vector["<<l<<"]:"<<a<<endl;
    }
    vector <int> v_o(v.begin(),v.end());
    int ls[m];
    for(int i=0;i<m;i++){
        v=v_o;
        int max=v.back(),min=v.front();
        cout<<"input val to find:";
        cin>>x;
        int l=n/2;
        int c;
        cout<<"find val:"<<x<<endl;
        cout<<"now vector:[";
        for(int i=0;i<v.size();i++){
            cout<<v[i]<<",";
        }
        cout<<"\b]"<<endl;
        cout<<"vector size:"<<v.size()<<endl;
        while(true){
            c=v[l];
            if(v.size()<=1){
                if(v.front()<x){
                    l=-1;
                    break;
                }else{
                    l=binary_search(v_o.begin(),v_o.end(),v[0]);
                    break;
                }
            }
            if(c!=x){
                if(x>c){
                    v.erase(v.begin(),v.begin()+l);
                    cout<<"\tnew vector:[";
                    for(int i=0;i<v.size();i++){
                        cout<<v[i]<<",";
                    }
                    cout<<"\b]"<<endl;
                    l=v.size()/2;
                }else{
                    v.erase(v.begin()+l,v.end());
                    cout<<"\tnew vector:[";
                    for(int i=0;i<v.size();i++){
                        cout<<v[i]<<",";
                    }
                    cout<<"\b]"<<endl;
                    l=v.size()/2;
                }
            }else{
                l=binary_search(v_o.begin(),v_o.end(),c);
                break;
            }
        }
        cout<<"find location:"<<l<<endl;
        ls[i]=l;
    }
    for(int i=0;i<m;i++){
        cout<<ls[i]<<endl;
    }
    return 0;
}