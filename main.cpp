#include <data.h>
#include <iostream>
#include <fstream>
#include <string>
#include <json.hpp>

using namespace std;




void build(string &name,const string &txt){
ofstream file(name);
if (file.is_open())
{
file << txt << endl;
file << name << endl;
file.close();
cout << "file printed" << endl;
}
}






int main(){


string pole = "banan";
data::txt(pole);

build(pole,"hahaha");



data::print("banan");
cout << "hi" << endl;







    return 0;
} 