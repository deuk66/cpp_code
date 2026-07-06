#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <array>
using namespace std;
//這份程式把書商版本的單字換成exam.cpp可以讀取的格式

bool last_is_dtxt(string s){
    if(s.length()<=3){
        return 0;
    }
    if(s.find(".txt")!=string::npos&&s.find(".txt")==s.length()-4) return true;
    return 0;
}
size_t find_last_alpha(string s){
    const string token="()-/";
    for(int i=s.length()-1;i>=0;i--){
        if(isalpha(s[i])||token.find(s[i])!=string::npos){
            return i;
        }
    }
    return string::npos;
}
bool is_all_not_alpha(string s){
    for(char &c:s){
        if(isalpha(c)||s.find_last_of("()/-")!=string::npos){
            return false;
        }
    }
    return true;
}
int main(){
    system("chcp 65001 > nul");
    bool logged=false;
    bool pipeout=true;
    bool type=true;
    string file_name="";
    string choose;
    cerr<<"type or fin?\n";
    cin>>choose;
    if(choose=="fin"){
        type=false;
    }
    cin.ignore();
    if(!type){//讀檔名
        cerr<<"enter input file name:\n";
        getline(cin,file_name);
        if(file_name.find('\\')!=string::npos){//開啟\log的辨識
            logged=((file_name[file_name.find('\\')+1])=='l')? true:false;
            file_name=file_name.substr(0,file_name.find('\\'));
        }
        while(file_name.length()<1||last_is_dtxt(file_name)){
            cerr<<"file name long error,type again:"<<endl;
            getline(cin,file_name);
        }
    }
    ifstream fin;
    if(!type){//開檔
        fin=ifstream(file_name+".txt");
    }
    
    cerr<<"pipe or fout?\n";
    cin>>choose;
    if(choose=="pipe") pipeout=true;
    cin.ignore();

    stringstream ss;//將每個getline的string變成輸出入流
    // 讀取整個檔案內容
    string line;
    string ts1,question,answer;

    struct word {//用來儲存一份單字含中英
        vector<string> questions={};
        string whole_question="";
        string answer="";
        word(string s1="",string s2=""){
            whole_question=s1;
            answer=s2;
        }
        void combine_question(){
            whole_question="";
            for(string s:questions){
                whole_question+=s+" ";
            }
            whole_question=whole_question.substr(0,whole_question.length()-1);//去除結尾空格符
        }
        void reset(){
            questions={};
            answer="";
            whole_question="";
        }

    };
    vector <word> wv;
    if(type){
        cerr<<"now typing,end type\"//end\":\n";
    }

    while(getline(type?cin:fin,line)){//讀取主幹    (type的cerr待補)
        if(line=="//end"){
            break;
        }
        ss.str(line);//開頭都初始化ss為line
        ss.clear();//將狀態位元清除(如讀取到底eof)
        if(line==""){//去除空白的行
            continue;
        }else if(isalpha(line[0])&&line[3]=='.'){//將月份標示排除
            continue;
        }else{//(如為題目)主程式
            ss.str(line.substr(line.find_first_of("....")+1));//將題號去除
            ss.clear();
            word w;
            w.reset();
            if(logged){
                cerr<<"now line:\n"<<line<<endl;
            }
            while(ss>>ts1){
                if(isalpha(ts1[0])&&ts1[ts1.length()-1]=='.'){//去詞性(頭是英文尾是'.')
                    continue;
                }else if(isalpha(ts1.back())&&isalpha(ts1[0])){//頭尾皆字母
                    w.questions.push_back(ts1);
                    if(logged){ cerr<<"all alpha "<<ts1<<endl;}
                }else{
                    if(logged){ cerr<<"answer round "<<ts1<<"\n";}
                    if(ts1.find('.')==string::npos){//將詞性分割
                        if(is_all_not_alpha(ts1)){
                            if(logged) cerr<<"all not alpha"<<endl;
                            w.answer=ts1;
                        }else{
                            if(logged) cerr<<"half alpha:";
                            w.answer=ts1.substr(find_last_alpha(ts1)+1);
                            w.questions.push_back(ts1.substr(0,find_last_alpha(ts1)+1));
                            if(logged) cerr<<"all alpha from "<<find_last_alpha(ts1)<<": "<<w.questions.back();
                            if(logged) cerr<<"all not alpha:"<<w.answer<<endl;
                        }
                    }else{
                        if(logged) cerr<<"have dot"<<endl;
                        w.answer=ts1.substr(ts1.find('.')+1);
                    }
                }
            }
            wv.push_back(w);
        }
        line="";
    }
    if(!type){
        fin.close();//關檔
    }

    //寫入exam.exe適用格式
    ofstream fout;
    if(!pipeout){
        cerr<<"enter output file name(don't type the file type):";
        getline(cin,file_name);
        while(file_name.length()<1||last_is_dtxt(file_name)){//檔案名錯誤或有".txt"
            cerr<<"file name long error,type again(don't type the file type):"<<endl;
            getline(cin,file_name);
        }
        fout=ofstream(file_name+".txt");
    }
    if(pipeout){
        cout<<"typing\n";
    }
    for(word w:wv){//逐一將題目拼裝並寫檔
        w.combine_question();
        if(pipeout){
            cout<<w.whole_question<<"\n";
            cout<<w.answer<<"\n";
        }else{
            fout<<w.whole_question<<"\n";
            fout<<w.answer<<"\n";
        }
    }
    //這裡暫時不管額外的中文，所以直接執行兩個//end
    if(pipeout){
        cout<<"//end"<<endl;
        cout<<"//end"<<endl;
    }else{
        fout<<"//end"<<endl;
        fout<<"//end"<<endl;
        fout.close();
    }
    if(pipeout){
        cerr<<"input filesave name,no file type:\n";
        cin>>file_name;
        cout<<file_name<<"\n";
        cout<<"\n";
        cout<<"\n";
    }
    return 0;
}