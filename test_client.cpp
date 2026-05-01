#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
    // 1. Создаем контекст ZMQ
    zmq::context_t context(1);

    // 2. Создаем сокет типа SUB (Subscriber — подписчик)
    zmq::socket_t subscriber(context, zmq::socket_type::sub);

    // 3. Подключаемся к адресу, который указан в сервере (твоем движке)
    subscriber.connect("tcp://localhost:5557");

    // 4. Важно: подписываемся на ВСЕ сообщения (пустая строка "" означает "всё")
    subscriber.set(zmq::sockopt::subscribe, "");

    std::cout << "Nexus Logger Client started..." << std::endl;
    std::cout << "Waiting for data from engine on port 5557..." << std::endl;

    while (true) {
        zmq::message_t reply;
        
        // Ожидаем сообщение (блокирующая функция)
        auto result = subscriber.recv(reply, zmq::recv_flags::none);
        
        if (result) {
            // Превращаем полученные байты в строку и выводим
            std::string msg(static_cast<char*>(reply.data()), reply.size());
            std::cout << "[LOG]: " << msg << std::endl;
        }
    }

    return 0;
}