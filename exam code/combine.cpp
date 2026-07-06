//這個程式專門把exam.cpp出來的題目合併在一份題目裡
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <cctype>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <ctime>
#include <stdlib.h>
using namespace std;


struct Question{
    string word;
    string answer;
    vector<string> options={"","","",""};
    Question(string Word="",string Answer="",vector<string> Options={"","","",""}){
        word=Word;
        answer=Answer;
        options=Options;
    }
};
int main (){
    system("chcp 65001 >> nul");
    string input="";
    vector <string> file_names;
    int file_number=0;
    cout<<"輸入第"<<file_number+1<<"份檔案名稱(不含副檔名)(結束輸入//end)"<<endl;
    while(getline(cin,input)){//輸入各檔案名稱
        if(input=="//end") break;
        file_names.push_back(input);
        file_number++;
        cout<<"輸入第"<<file_number+1<<"份檔案名稱(不含副檔名)(結束輸入//end)"<<endl;
    }
    vector <Question> Questions;
    int total_ans_count=0;
    for(int k=0;k<file_names.size();k++){//string& file_name:file_names
        int file_count=0;//初始化 v
        string file_name=file_names[k];
        Question q("","",{"","","",""});//初始化^
        ifstream fin(file_name+".txt");
        cout<<"開啟"<<file_name<<endl;
        if(!fin){
            continue;
        }
        string line;
        //從這裡開始讀取
        while (getline(fin, line) && line.find("========== 答案 ==========") == string::npos&&cout<<line.find("========== 答案 ==========")<<endl) {
            if (line.empty() || !isdigit(line[0])) continue; // 跳過空行或非題目行

            // 找到第一個 '.' 之後的位置
            size_t dot_pos = line.find('.');
            size_t a_pos = line.find("(A)");
            q.answer="";//初始化
            q.options={"","","",""};
            q.word="";
            if (dot_pos != string::npos && a_pos != string::npos) { //有.有(A)
                q.word = line.substr(dot_pos + 1, a_pos - dot_pos - 2); //切出問題
                cout<<q.word<<endl;
                // 讀取四個選項
                q.options[0]=(line.substr(line.find("(A)") + 3, line.find("(B)") - line.find("(A)") - 4));
                q.options[1]=(line.substr(line.find("(B)") + 3, line.find("(C)") - line.find("(B)") - 4));
                q.options[2]=(line.substr(line.find("(C)") + 3, line.find("(D)") - line.find("(C)") - 4));
                q.options[3]=(line.substr(line.find("(D)") + 3,line.length()-line.find("(D)")-4));
                for(int i=0;i<4;i++){
                    cout<<q.options[i];
                }
                Questions.push_back(q);
                file_count++;
            }
        }
        int ans_count=0;//找答案
        char c;
        while(fin>>c){
            if(c<='D'&&c>='A'){
                if(ans_count<file_count){
                    Questions[total_ans_count].answer=c;
                    cout<<total_ans_count<<"題答案是"<<c<<endl;
                    ans_count++;
                    total_ans_count++;
                }
            }
        }
        fin.close();
    }
    cout<<"\n\n\n\n\nQuestions:"<<endl;
    for(Question& q:Questions){
        cout<<q.word<<endl;
        for(string &s:q.options){
            cout<<s<<"  ";
        }
        cout<<endl;
        cout<<q.answer<<endl;
    }
    if (Questions.empty()) {
        cout << "沒有讀取到任何題目。" << endl;
        return 0;
    }
    string outfile_name;
    cout<<"輸入儲存檔案名稱(不含副檔名)"<<endl;
    cin>>outfile_name;
    ofstream fout(outfile_name+".txt");
    int question_count=0;
    //寫入BOM
    unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    fout.write((char*)bom, sizeof(bom));
    fout<<"========== 測驗題目 ==========\n\n";
    cout<<"========== 測驗題目 ==========\n\n";
    string option_label[4]={"(A)","(B)","(C)","(D)"};
    for(Question &q:Questions){
        question_count++;
        fout<<question_count<<"."<<q.word<<"\t";
        cout<<question_count<<". "<<q.word<<"  ";
        for(int i=0;i<4;i++){
            fout<<option_label[i]<<" "<<q.options[i]<<'\t';
            cout<<option_label[i]<<" "<<q.options[i];
        }
        fout<<"\n\n";
        cout<<"\n\n";
    }
    fout<<"========== 答案 ==========\n";
    cout<<"========== 答案 ==========\n";
    for(int i=0;i<Questions.size();i++){
        if(i%5==0){
            fout<<'\n'<<i+1<<'~'<<i+5<<((i==0)?"\t\t":"\t");
            cout<<'\n'<<i+1<<'~'<<i+5<<" : ";
        }
        fout<<Questions[i].answer<<" ";
        cout<<Questions[i].answer;
    }
    fout.close();
    cout<<"檔案儲存完畢"<<endl;
    cout<<"按任意鍵結束"<<endl;
    getch();
    return 0;
}