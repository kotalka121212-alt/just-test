#pragma once
#include <includes.h>

using namespace std;
using json = nlohmann::json;

namespace data{
    
void print(string a);
string txt(string &a, const string &obj);
void build(const string &name,const string &txt);

class file{
    private:
    string file_name;

    public:

//makefile
file(string &name);

//print в файл
void file_pr(const string &a);
void file_pr(const json &a);
void file_pr(const char* a);






};



}