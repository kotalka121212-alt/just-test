#include <data.h>
#include <iostream>
#include <fstream>
#include <string>
#include <json.hpp>

using namespace std;


string txt(string &a)
{
    return a = "../" + a + ".txt";
}

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
txt(pole);

build(pole,"dildo hahaha");



data::print("banan");
cout << "hi" << endl;







    return 0;
} 