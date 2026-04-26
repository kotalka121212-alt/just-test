
#define STB_IMAGE_IMPLEMENTATION

#include <data.h>
#include <jsones.h>
#include <includes.h>
#include <myiterator.h>

#include <shader.h>
#include "inc_gr.h"
#include <grafics.h>

using namespace std;
using json = nlohmann::json;


int main(){
setlocale(LC_ALL, "ru_RU.UTF-8");
//*iter::choose();






    try {
        GLFW glfw; // Старт GLFW
        Window w(600, 800, "Nexus Engine");
        w.setIcon("../photo.png");
        
        w.loop();

    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return -1;
    }

    return 0;
} 
