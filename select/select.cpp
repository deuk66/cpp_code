#include<vector>
#include<string>
#include<array>
#include<iostream>
#include<fstream>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
void output(
    string s1,//with tips
    string s2,//not
    bool tips
    ){
    if(tips){
        cout<<s1<<endl;
    }
    else{
        cout<<s2<<endl;
    }
}
int main() {
    // Enable UTF-8 output on Windows console so Chinese can be displayed
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    while(true){
        string input="";
        vector <string> datas;
        size_t type = 0;
        bool tips=true;
        cout<<"need tips? (y/n):";
        cin>>input;
        cin.ignore();
        if(input=="y"||input=="Y"){
            tips=true;
        }
        else{
            tips=false;
        }
        // cout<< "select \"input\"(1) or \"output\"(2):";
        output(
            "select \"input\"(1) or \"output\"(2):",
            "input or output?:",
            tips
        );
        cin>>type;
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            type = 0;
        }
        cin.ignore();

    //type 1: input
    if(type==1){
        // cout<<"select type( 1.all in2.one by one):";
        output(
            "select type( 1.all in 2.one by one):",
            "all or one by one?:",
            tips
        );
        cin>>type;
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            type = 0;
        }
        cin.ignore(); // always clear the newline after reading type

        //type 1: all in one line
        if(type==1){
            cout<<"enter some data:";
            string line="";
            getline(cin, line);
            string current = "";
            while(line!="//end"){ 
                current = "";
                line="";
                cout<<"enter some data:";
                getline(cin, line);
                if(line=="//end"){
                    break;
                }
                for(size_t n=0; n<line.length(); n++){
                    char c = line[n];
                    if(c==','||c==' ' || c=='\n' || c=='\0'|| c==';'|| c=='.'|| c=='\t'){
                        if(current.length() > 0){
                            datas.push_back(current);
                            current = "";
                        }
                    }
                    else {
                        current += c;
                    }
                    
                    if(current.length() > 0){
                        datas.push_back(current);
                    }
                }
            }
        }
        //type 2: one by one
        else if(type==2){
            input="";
            // cout<<"enter some data one by one(type\"//end\" to stop):";
            output(
                "enter data one by one(type\"//end\" to stop):",
                "input data :",
                tips
            );
            while(input!="//end"){
                cin>>input;
                cin.ignore();
                if(input!="//end")
                    datas.push_back(input);
                if(input=="//end"){
                    break;
                }
            }
        }
        //save data to txt file
        cout<<"input a file name to save data:";
        getline(cin, input);
        ofstream outfile(input);
        for(auto data:datas){
            outfile<<data<<"\n";
        }
        outfile.close();
    }
    //type 2: output

    else if(type==2){
    //select file
        cout<<"input a file name to read data:"<<endl;
        string filename;
        cin>>filename;
        ifstream infile(filename);
        // prepare containers in outer scope so they remain available for output stage
        vector<string> allDatas;
        bool pined=false;
        size_t pinPos=0;
        size_t baseIndex=0;
        datas.clear();
        if(!infile){
            cout<<"failed to open file: "<<filename<<endl;
            return 1;
        } else {
            string line;
            size_t index=0;
            while(getline(infile,line)){
                allDatas.push_back(line);
                if(!pined && line.find("//pin") != string::npos){
                    pined=true;
                    pinPos=index;
                }
                index++;
            }
            infile.close();
            // keep a full copy and set defaults
            datas = allDatas;

            cout<<"file readed"<<endl;
            // if pin found, ask whether to read after pin
            if(!pined){
                cout<<"no pin found"<<endl;
            }
            else {
                output(
                    "found pin, read after pin? (y/n):",
                    "found pin, read after pin?:",
                    tips
                );
                string yn;
                cin>>yn;
                cin.ignore();
                if(yn=="y"||yn=="Y"){
                    // set datas to only lines after pin
                    baseIndex = pinPos + 1;
                    if(baseIndex <= allDatas.size()){
                        datas.assign(allDatas.begin()+baseIndex, allDatas.end());
                    } else {
                        datas.clear();
                    }

                    output(
                        "delete pin from file? (y/n):",
                        "delete pin from file?:",
                        tips
                    );
                    cin>>yn;
                    cin.ignore();
                    if(yn=="y"||yn=="Y"){
                        // remove only the pin line from the full file (preserve other lines)
                        if(pinPos < allDatas.size()){
                            allDatas.erase(allDatas.begin()+pinPos);
                            // adjust baseIndex if needed
                            if(baseIndex > 0 && baseIndex > pinPos) baseIndex--;
                        }
                        ofstream outfile(filename);
                        for(auto &d: allDatas) outfile<<d<<"\n";
                        outfile.close();
                        // recompute datas based on possibly adjusted baseIndex
                        if(baseIndex <= allDatas.size()){
                            datas.assign(allDatas.begin()+baseIndex, allDatas.end());
                        } else datas.clear();
                    }
                }
            }
        }
        //select output type
        output(
            "select type( 1.all out\n2.one by one):",
            "all or one by one?:",
            tips
        );
        cin>>type;
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            type = 0;
        }
        cin.ignore();
        //type 1: all out
        if(type==1){
            cout<<"here is all data:";
            bool end=false;
            size_t idx=0;
            while(!end){
                for(size_t i=0;i<5;i++){
                    if(idx < datas.size()){
                        cout<<datas[idx]<<'\t';
                        idx++;
                    }
                    else{
                        end=true;
                        break;
                    }
                }
                cout<<endl;
            }
            cout<<endl;
            cout<<"end of data";
        }
        //type 2: one by one
        else if(type==2){
            output(
                "here is data one by one(type\"//end\" to stop):",
                "here is data one by one:",
                tips
            );
            for(size_t i=0;i<datas.size();i++){
                cout<<datas[i]<<endl;
                output(
                    "next?\n(type\"//end\" to stop,type\"//pin\" to place a pin):",
                    "next?:",
                    tips
                );
                getline(cin, input);
                if(input=="//end"){
                    break;
                }
                else if(input=="//pin"){
                    cout<<"pinned data: "<<datas[i]<<endl;
                    // compute global index in allDatas and insert pin before that line
                    size_t globalIndex = baseIndex + i;
                    if(globalIndex <= allDatas.size()){
                        allDatas.insert(allDatas.begin()+globalIndex, string("//pin"));
                    } else {
                        allDatas.push_back(string("//pin"));
                        globalIndex = allDatas.size()-1;
                    }
                    // write full file back (only pin line added)
                    ofstream outfile(filename);
                    for(auto &d: allDatas) outfile<<d<<"\n";
                    outfile.close();
                    // update baseIndex to point to the line after the newly inserted pin
                    baseIndex = globalIndex + 1;
                    // recompute datas to be lines after the new pin
                    if(baseIndex <= allDatas.size()) datas.assign(allDatas.begin()+baseIndex, allDatas.end()); else datas.clear();
                    cout<<"pin added and file updated"<<endl;
                    // // 暫停: 要繼續迭次嗎？(按 Enter 繼續，輸入 //end 結束)
                    // Pause and ask whether to continue iteration
                    output(
                        "Paused: continue iteration? (Enter to continue, //end to exit)",
                        "Paused: continue?",
                        tips
                    );
                    getline(cin, input);
                    if(input=="//end") break;
                    // 按 Enter 或其他非 //end 輸入將繼續下一筆
                }
            }
            cout<<"end of data";
        }
    }else{
        cout<<"input error, restart program"<<endl;
        return 1;
    }
        // ask whether to exit or restart after finishing the run
        output(
            "Program finished. Exit program? (y/n):",
            "Program finished. Exit program?:",
            tips
        );
        cin>>input;
        cin.ignore();
        if(input=="y"||input=="Y"){
            break;
        }
        // otherwise loop and restart
    }
    return 0;
}