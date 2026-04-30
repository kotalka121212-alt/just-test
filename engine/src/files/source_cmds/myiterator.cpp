#include <myiterator.h>

using namespace neyrons;


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

void iter::newNeyron(){
    double mill = 62.1371;
    double km = 100;
    neyron neyr;

    int i = 0;

    do
    {
        i++;

        neyr.train(km,mill);
        if(i%10 == 0)
    {
        cout << "iteration:    " << i << "error:   " << neyr.lastError;
    }

    }while(neyr.lastError > neyr.smooth || neyr.lastError < -neyr.smooth);

    

    cout << endl << endl;
    cout << "millies: " << neyr.Processinput(km) << endl <<  "km: " << km << endl;
    cout << "millies: " << neyr.Processinput(200) << endl <<  "km: " << 200 << endl;

};

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
case 4:iter::newNeyron();break;
}
}
