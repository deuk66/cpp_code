#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void cls() {
    cout << "\033[2J\033[1;1H";
    cout.flush();
}

struct node {
    bool full=0;
    int data;
    int level=0;
    node* small=nullptr;
    node* big=nullptr;
    node* undo=nullptr;
    int size;
    node(int l=0):level(l){//建構子
        cout<<"node"<<level<<" spawn"<<endl;
    }
    ~node(){
        cout<<"node"<<level<<" delete"<<endl;
        if(big!=nullptr){
            delete big;
        }
        if(small!=nullptr){
            delete small;
        }
    }
    void input(int a){
        if(!full){
            data=a;
            full=1;
        }else{
            if(a>=data){
                if(big==nullptr){
                        big=new node(level+1);
                        big->input(a);
                }else{
                    big->input(a);
                }
            }else{
                if(small==nullptr){
                        small=new node(level+1);
                        small->input(a);
                }else{
                    small->input(a);
                }
            }
        }
    }
    void output(){
        if(small!=nullptr)  small->output();
        cout<<data<<" ";
        if(big!=nullptr)  big->output();
    }
    void output(bool b){//output-sort
        if(big!=nullptr)    big->output(true);
        for(int i=0;i<level;i++){
            cout<<"\t";
        }
        cout<<data<<endl;
        if(small!=nullptr)  small->output(true);
    }
    
};
int main (){
    node tree(0);
    int input;
    while(cin>>input){
        cls();
        tree.input(input);
        tree.output(1);
    }
    cout<<endl;
    return 0;
}