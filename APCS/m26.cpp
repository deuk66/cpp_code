#include <vector>
#include <iostream>
using namespace std ;
int stair(int a){
    if(a==1||a==2){
        return a;
    }
    return stair(a-1)+stair(a-2);
}
int main (){
    int a=0;
    cin>>a;
    cout<<stair(a);
    return 0;
}