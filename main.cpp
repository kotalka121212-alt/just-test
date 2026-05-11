
#define STB_IMAGE_IMPLEMENTATION

#include <SDL3/SDL.h>

#include <nexus_alg.h>
#include "includes.h"
#include <shader.h>
#include <grafics.h>

#include <zmq.hpp>




using namespace std;
using namespace NexAlg;
using json = nlohmann::json;




int main(int argc, char *argv[]){
setlocale(LC_ALL, "ru_RU.UTF-8");


vector<int> buba = {0,0,1};
buba = NexAlg::move0(buba);
int i = 0;
while(i < buba.size()){
cout << buba[i];
i++;
}

cout << "\n";

vector<int> swag = {1,3,66,2,88,11};

vector<int>::iterator it;

it = swag.begin(); 
it += 4;

cout << *it << endl;














    try {
        GLFW glfw; // Старт GLFW
        Window w(600, 800, "Nexus");
        w.setIcon("../photo.png");
        
        w.loop();

    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return -1;
    }




    return 0;
} 
