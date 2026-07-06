#include <iostream>
#include <vector>
using namespace std;
bool test2(string s){
    for(int i=0;i<s.length();i++){
        if(s[i]>='A'&&s[i]<='Z'){
            return 1;
        }
    }
    return 0;
}//大寫

bool test3(string s){
    for(int i=0;i<s.length();i++){
        if(s[i]>='a'&&s[i]<='z'){
            return 1;
        }
    }
    return 0;
}//小寫

bool test4(string s){
    for(int i=0;i<s.length();i++){
        if(isdigit(s[i])){
            return 1;
        }
    }
    return 0;
}//包含數字

bool test5(string s){
    string str="??";
    for(int i=0;i<s.length();i++){
        str[0]=str[1];
        str[1]=str[2];
        str[2]=s[i];
        if(str[0]==str[1]&&str[1]==str[2]&&str[2]==str[3]){
            return 0;
        }
    }
    return 1;
}//不超過三個連續字元

bool test(string s,int option){
    /*if(option==0){
        
    }*/
    if(option==0){
        if(s.length()>=8){
            return 1 ;
        }
        return 0;
    }
    else if(option==1){
        return test2(s);
    }else if(option==2){
        return test3(s);
    }else if(option==3){
        return test4(s);
    }else if(option==4){
        return test5(s);
    }
    
}//test1 and test2~5

string low(string s){
    for(int i=0;i<s.length();i++){
        if(s[i]>='A'&&s[i]<='Z'){
            s[i]+=('a'-s[i]);
        }
    }
    return s;
}

bool test6(string acc,string pas){
    string a=acc;
    acc=low(acc);
    string p=pas;
    pas=low(pas);
    if(p.find(a)!=string::npos){
        return 0;
    }
    else{
        return 1;
    }
}

int main(){
    int n=0;
    cin>>n;
    string acc[n];
    string pas[n];
    bool b[n][6];
    int passq[n];
    for(int i=0;i<n;i++){
        cin>>acc[i];
        cin>>pas[i];
    }//for測資
    
    for(int i=0;i<n;i++){
        for(int j=0;j<6;j++){
            b[i][j]=0;
        }
    }//初始化b陣列,1為 pass
    for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            if(test(pas[i],j)){
                b[i][0]=1;
                passq[i]++;
            }
        }
        if(test6(pas[i],acc[i])){
            b[i][0]=1;
            passq[i]++;
        }
    }//呼叫測驗函數
    bool pass[n];
    for(int i=0;i<n;i++){//1為pass
        if (passq[i]==6){
            pass[i]=1;
        }
    }//pass Safe==1
    string passkey[2]={"Safe","Unsafe"};
    
    for(int i=0;i<n;i++){
        cout<<acc[i]<<" "<<passkey[int (!(pass[i]))];
        if(!pass[i]){
            for(int j=0;j<6;j++){
                if(b[i][j]){
                    cout<<j<<" ";
                }
            }
        }
        cout<<"\n";
    }//output
    int allq=0;
    for(int i=0;i<n;i++){
        if(pass[i]){
            allq++;
        }
    }
    cout<<passkey[0]<<" "<<allq<<"\n";
    int upasstestnum[6];
    for(int i=0;i<n;i++){
        for(int j=0;j<6;j++){
            if(b[i][j]){
                upasstestnum[j]++;
            }
        }
    }
    int maxuptn=-1;
    for(int i=0;i<6;i++){
        if(upasstestnum[i]>=maxuptn){
            maxuptn=upasstestnum[i];
        }
    }
    cout<<"Most: "<<maxuptn;
    return 0;
}