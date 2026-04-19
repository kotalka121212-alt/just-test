#include <myiterator.h>

void iter::make_file(){
json fil;
fil["name"] = "banan";
fil["kolichestvo"] = 21;
fil["arr"] = {"2","52","42","67"};


string jsn = "2";
data::txt(jsn,"json");

data::file jason(jsn);
jason.file_pr(fil);



}

void iter::choose(){
    int a;
data::print("choose your tool");
cin >> a; cout << endl;
switch (a){
case 1:make_file();break;
}
}
