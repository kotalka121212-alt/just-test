
#define STB_IMAGE_IMPLEMENTATION

#include <data.h>
#include <includes.h>
#include <myiterator.h>

#include <shader.h>
#include "inc_gr.h"
#include <grafics.h>

#include <zmq.hpp>

using namespace std;
using json = nlohmann::json;


int main(){
setlocale(LC_ALL, "ru_RU.UTF-8");

zmq::context_t context(1);

    // 2. Создаем PUB-сокет (издатель). Он идеально подходит для сервера, 
    // который рассылает команды всем подключенным "нексусам".
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    
    try {
        // Привязываем сокет к порту. "*" значит "все интерфейсы".
        publisher.bind("tcp://*:5555");
        std::cout << "[Nexus] Server started on port 5555" << std::endl;
    } catch (const zmq::error_t& e) {
        std::cerr << "[ZMQ Error] " << e.what() << std::endl;
    }



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
