#include <iostream>
#include <cmath>
int main(){
        for(int i=1;i<=10000000;i*=10){
            std::cout<<"\t";
            for(int j=i-i;j<i*10;j+=i){
                std::cout<<j<<"\t";
            }
            std::cout<<std::endl;
            std::cout<<"\t";
            for(int j=i-i;j<i*10;j+=i){
                std::cout<<j%8<<"\t";
            }
            std::cout<<std::endl<<std::endl;
        }
    return 0;
}