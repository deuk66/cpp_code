#include <iostream>
struct node{
    char data;
    int size;
    node& next;
};
int size(int a){
    int i=0;
    for(i=0;a>0;i++){
        a/=10;
    }
    return i;
}
node adder(node a,node b,node l){
}
    