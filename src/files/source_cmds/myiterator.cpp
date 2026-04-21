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

void iter::maths(){
    int a = 1;
    data::print("what: ");
    cin >> a; cout << endl;
    cout << kt_math::faktor(a) << endl;
};

void iter::destory_file(){
    data::file::destroyfile("../spawn_files/2.json");
}

void iter::choose(){
    int a;
data::print("choose your tool");
cin >> a; cout << endl;
switch (a){
case 1:make_file();break;
case 2:iter::destory_file();break;
case 3:iter::maths();break;
}
}
