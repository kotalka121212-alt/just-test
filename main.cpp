
#define STB_IMAGE_IMPLEMENTATION




#include "includes.h"
#include <shader.h>
#include <grafics.h>

#include <zmq.hpp>


#include <QApplication>
#include <QPushButton>
#include <QMessageBox>

using namespace std;
using json = nlohmann::json;


int main(int argc, char *argv[]){
setlocale(LC_ALL, "ru_RU.UTF-8");





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
