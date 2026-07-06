#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <conio.h>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct Question {
    string word;
    string correct_answer;
    vector<string> options;
};

void cls(){
    system("cmd /c cls");
}
int ran(int n) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    return rand() % (n + 1);
}
int n;
vector <string> words;
vector <string> answers;
void input_by_typing(){
    string temp_string="";
    int word_count=0;
    cout<<"輸入第"<<word_count+1<<"題題目(輸入\"//end\"停止輸入):";
    //避免使用者出現空格，用getline取代cin
    //輸入題目和答案
    cin.ignore();
    while(true){
        getline(cin,temp_string);
        if(temp_string=="//end"){
            break;
        }
        words.push_back(temp_string);
        cls();
        cout<<"第"<<word_count +1<<"題題目是:\""<< words[word_count] << "\""<<endl;
        cout<<"輸入第"<<word_count+1<<"題答案:";
        getline(cin,temp_string);
        answers.push_back(temp_string);
        cout<<"第"<<(word_count+1)<<"題答案是:\""<<answers[word_count]<<"\""<<endl;
        ++word_count;
        cout<<"輸入第"<<word_count+1<<"題題目:";
    }

    cout<<"輸入額外混入的答案 (如無需則輸入//end):"<<endl;
    while(true){
        getline(cin,temp_string);
        if(temp_string!="//end"){
            cls();
            cout<<"混入答案:"<<temp_string;
            answers.push_back(temp_string);
        }else{
            break;
        }
    }
    n=word_count;
}
void input_by_fstream(){
    //全部同打字法但用fstream
    cout<<"輸入文件名稱(不含副檔名):"<<endl;
    string filename;
    getline(cin,filename);
    while(true){
        if(filename.length()>=4&&filename.substr(filename.length()-4)==".txt"){
            cout<<"輸入錯誤，請去除副檔名再輸入:"<<endl;
            getline(cin,filename);
        }else{
            break;
        }
    }
    ifstream fin(filename);
    string temp_string="";
    int word_count=0;
    while(true){
        getline(fin,temp_string);
        if(temp_string=="//end"){
            break;
        }else{
            words.push_back(temp_string);
        }
        // getline(cin,temp_string);
        ++word_count;
    }
    while(true){
        getline(fin,temp_string);
        if(temp_string!="//end"){
            answers.push_back(temp_string);
        }else{
            break;
        }
    }
    fin.close();
    n=word_count;
}

vector <array <string , 5> > questions;//[0]放單字，[1]~[4]放選項
int main() {
    string choose;
    system("chcp 65001");
    //設定成繁體中文
    cout<<"輸入使用typing或fstream?"<<endl;
    cin>>choose;
    if(choose=="typing"){
        input_by_typing();
    }else{
        input_by_fstream();
    }
    //將word和answer混成question
    // 初始化隨機數產生器
    random_device rd;
    mt19937 g(rd());

    // 建立題目索引並打亂 (決定出題順序)
    vector<int> indices(n);
    for(int i = 0; i < n; ++i) indices[i] = i;
    shuffle(indices.begin(), indices.end(), g);

    // 產生題目
    vector<Question> all_questions;
    for (int i = 0; i < n; ++i) {
        int current_idx = indices[i];
        Question q;
        q.word = words[current_idx];
        q.correct_answer = answers[current_idx];

        // 建立干擾項池：排除目前的正確答案
        vector<string> distractors;
        for (int j = 0; j < (int)answers.size(); ++j) {
            if (answers[j] != q.correct_answer) {
                distractors.push_back(answers[j]);
            }
        }

        // 隨機打亂干擾項並取前三個
        shuffle(distractors.begin(), distractors.end(), g);
        
        q.options.push_back(q.correct_answer);
        for (int k = 0; k < 3 && k < (int)distractors.size(); ++k) {
            q.options.push_back(distractors[k]);
        }

        // 再次打亂四個選項的位置
        shuffle(q.options.begin(), q.options.end(), g);

        all_questions.push_back(q);
    }

    // 輸出結果到文件
    cout << "輸入要儲存的檔案名稱 (不含副檔名): ";
    string filename;
    getline(cin, filename);
    filename += ".txt";
    
    ofstream outFile(filename);
    if (!outFile) {
        cout << "無法建立檔案！" << endl;
        return 1;
    }
    //加BOM
    unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    outFile.write((char*)bom, sizeof(bom));
    // 寫入題目到文件
    outFile << "========== 測驗題目 ==========" << endl << endl;
    for (int i = 0; i < (int)all_questions.size(); ++i) {
        outFile<< i + 1 << "." << all_questions[i].word <<"\t";// 1.xxx
        char label = 'A';
        for (const string& opt : all_questions[i].options) {
            outFile << "(" << label++ << ")" << opt<<"\t"; //(X)xxxx
        }
        outFile << endl<<endl;
    }
    
    // 寫入答案（另一個區塊）
    outFile << endl << "========== 答案 ==========" << endl << endl;
    
    // 收集所有答案的選項代號
    vector<char> answer_labels;
    for (int i = 0; i < (int)all_questions.size(); ++i) {
        char correct_label = '?';
        for (int j = 0; j < (int)all_questions[i].options.size(); ++j) {
            if (all_questions[i].options[j] == all_questions[i].correct_answer) {
                correct_label = 'A' + j;
                break;
            }
        }
        answer_labels.push_back(correct_label);
    }
    
    // 以每5題為一組輸出
    for (int i = 0; i < (int)answer_labels.size(); i += 5) {
        int start = i + 1;
        int end = min(i + 5, (int)answer_labels.size());
        outFile << start << "~" <<end<<"\t";
        if(i==0){
            outFile<<"\t";
        }
        for (int j = i; j < end; ++j) {
            outFile << answer_labels[j];
            if (j < end - 1) outFile << " ";
        }
        outFile << endl;
    }
    
    outFile.close();
    cout << "測驗已儲存至 " << filename << endl;
    
    return 0;
}