#include <data.h>
#include <jsones.h>
#include <includes.h>

using namespace std;
using json = nlohmann::json;



int main(){

json fil;
fil["name"] = "banan";
fil["kolichestvo"] = 21;
fil["arr"] = {"2","52","42","67"};

string pole = "banan";
data::txt(pole, "txt");


string jsn = "2";
data::txt(jsn,"json");

data::file a(jsn);
data::file e(pole);
e.file_pr("da");
a.file_pr(fil);

    return 0;
} 