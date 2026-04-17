#include <data.h>
#include <iostream>
#include <string>

using namespace std;
using date = data::datas;

void data::print(std::string a)
{
cout << a << endl;
}

string data::txt(string &a)
{
    return a = "../" + a + ".txt";
}





