#include <data.h>
#include <jsones.h>
#include <iostream>
#include <fstream>
#include <string>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;



int main(){


string pole = "banan";
data::txt(pole);


json fil;
fil["name"] = "banan";
fil["kolichestvo"] = 21;
fil["arr"] = {"2","52","42","67"};

ofstream file("../1.json", std::ios::app);
if (file.is_open())
{
file << fil << endl;
file.close();
cout << "file printed" << endl;
}


data::datas e(pole,"hahaha");

data::print("banan");
cout << "hi" << endl;




    return 0;
} 