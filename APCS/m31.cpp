#include <iostream>
#include <vector>
#include <string>
int main(){
    std::string s;
    std::cin>>s;
    std::vector<short> a,b,total;
    for(char c:s){
        short i=c-'0';
        a.insert(a.begin(),i);
    }
    std::cin>>s;
    for(char c:s){
        short i=c-'0';
        b.insert(a.begin(),i);
    }
    auto&& p=((a.size()>b.size())?(&b):(&a));
    auto&& pp=((a.size()>b.size())?(&a):(&b));
    for(int i=0;i<p->size();i++){
        total.push_back((*p)[i]+(*pp)[i]);
    }
    for(int i=0;i<total.size();i++){
        if(total[i]>9){//carry
            if(total.size()-1<i){
                total.insert(total.begin(),0);
            }
            total[i+1]++;
        }
    }
    bool showz=0;
    while(total.size()>0&&total.front()==0){
        total.erase(total.begin());
    }
    for (short i=total.size()-1;i>=0;i--) {
        std::cout<<total[i];
    }    
    return 0;
}