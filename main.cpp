#include <data.h>
#include <jsones.h>
#include <includes.h>
#include <myiterator.h>



using namespace std;
using json = nlohmann::json;



int main(){

json fil;
fil["name"] = "banan";
fil["kolichestvo"] = 21;
fil["arr"] = {"2","52","42","67"};


string jsn = "2";
data::txt(jsn,"json");

data::file jason(jsn);
jason.file_pr(fil);










    return 0;
} 