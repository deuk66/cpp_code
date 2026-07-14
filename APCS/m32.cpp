#include <iostream>
#include <stdlib.h>

int binary_search(const int arr[],const int a,int down=0,int up=0,int level=0){
    // std::cerr<<"目前範圍:";
    for(int i=down;i<=up;i++){
        // std::cerr<<arr[i]<<"\t";
    }
    // std::cerr<<std::endl;
    if(level==0){
        if (a>arr[up]||a<arr[down]){
            // std::cerr<<"範圍外";
            return -1;
        }
        level++;
    }
    int mid=(down+up)/2;
    // std::cerr<<"middle位置:"<<mid<<" 值為"<<arr[mid]<<std::endl;
    
    if(up-down<=1){
        return down;
    }else if(arr[mid]==a){
        // std::cerr<<"找到值"<<arr[mid]<<std::endl;
        return mid;
    }else if(a>arr[mid]){
        // std::cerr<<"位置在右半邊:"; for(int i=mid;i<=up;i++){std::cerr<<arr[i]<<' ';} std::cerr<<std::endl;
        return binary_search(arr,a,mid,up,level);
    }else if(a<=arr[mid]){
        // std::cerr<<"位置在左半邊:"; for(int i=down;i<=mid;i++){std::cerr<<arr[i]<<' ';} std::cerr<<std::endl;
        return binary_search(arr,a,down,mid,level);
    }else{
        // std::cerr<<"發生預期外錯誤"<<std::endl;
        return -1;
    }
}


int main(){
    system("chcp 65001");
    int n=0;
    std::cin>>n;
    int arr[n];
    for(int &i:arr){
        std::cin>>i;
    }
    int ans;
    std::cin>>ans;
    int answer=binary_search(arr,ans,0,n-1);
    std::cout<<"找到數值位置:"<<answer<<std::endl;
    std::cout<<"值為:"<<arr[answer]<<std::endl;
    return 0;
}

