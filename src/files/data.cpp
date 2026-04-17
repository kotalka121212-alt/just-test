#include <data.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


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

string data::txt(string &a)
{
    return a = "../" + a + ".txt";
}

data::datas::datas(string &name,const string &txt){
ofstream file(name);
if (file.is_open())
{
file << txt << endl;
file << name << endl;
file.close();
cout << "file printed" << endl;
}

}





