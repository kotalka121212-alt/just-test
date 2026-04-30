#pragma once
#include <includes.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using json = nlohmann::json;

namespace data{
    
void print(std::string a)
{
cout << a << endl;
}

string txt(string &a,const string &obj)
{
    return a = "../spawn_files/" + a + '.' + obj;
}

void build(const string &name,const string &txt){
ofstream file(name);
if (file.is_open())
{
file << txt << endl;
file << name << endl;
file.close();
cout << "file printed" << endl;
}
}

class file{
    private:
    string file_name;

    public:

//?makefile
file(string &name){
file_name = name;
ofstream file(name);
cout << "file printed" << endl;
}


//!deletefile
static void destroyfile(const string &name){
if(filesystem::remove(name)){
    cout << "file " << name << " deleted!" << endl;
}
else {cout << "file " << name << " cannot delete" << endl;}
};




//print в файл
void file_pr(const string &a){
ofstream file(this->file_name);
if (file.is_open()){
    file << a << endl;
    cout << "printed " << a << " in file" << endl;
    file.close();
}
};

void file_pr(const json &a){
ofstream file(this->file_name);
if (file.is_open()){
    file << a.dump(4) << endl;
    cout << "printed " << a.dump(4) << " in file" << endl;
    file.close();
}
};

void file_pr(const char* a) {
    file_pr(std::string(a));  // просто вызываем string версию
}


//read из файла



};



}