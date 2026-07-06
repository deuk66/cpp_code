#include <string>
#include "tool.h"
#include <cmath>
#include <iostream>
using namespace std;

struct gray_code{
    
    void gray(string g[]){
        size_t size=size(g);
        for(size_t i=0;i<size;i++){
            
        }
    }
};

int main(){
    gray_code gray;
    int input;
    cout<<"請輸入格雷碼位元數:";
    cin>>input;
    string gray_array[int(pow(2,input))];
    for(int i=0;i<size(gray_array);i++){
        gray_array[i]="";
    }
    gray_array[0]="0";
    gray_array[1]="1";
    for(int i=0;i<input-1;i++){
        
    }
    return 0;
}