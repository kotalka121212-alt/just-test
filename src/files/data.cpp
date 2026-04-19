#include <data.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using json = nlohmann::json;

void data::build(const string &name,const string &txt){
ofstream file(name);
if (file.is_open())
{
file << txt << endl;
file << name << endl;
file.close();
cout << "file printed" << endl;
}
}

void data::print(std::string a)
{
cout << a << endl;
}

string data::txt(string &a,const string &obj)
{
    return a = "../spawn_files/" + a + '.' + obj;
}

data::file::file(string &name){
data::file::file_name = name;
ofstream file(name);
cout << "file printed" << endl;
}

void data::file::file_pr(const string &a){
ofstream file(data::file::file_name);
if (file.is_open()){
    file << a << endl;
    cout << "printed " << a << " in file" << endl;
    file.close();
}
};

void data::file::file_pr(const json &a){
ofstream file(data::file::file_name);
if (file.is_open()){
    file << a.dump(4) << endl;
    cout << "printed " << a.dump(4) << " in file" << endl;
    file.close();
}
};

void data::file::file_pr(const char* a) {
    file_pr(std::string(a));  // просто вызываем string версию
}

