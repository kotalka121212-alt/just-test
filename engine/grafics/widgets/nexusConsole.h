

#pragma once
#include "inc_gr.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <zmq.hpp>



class NexusCommandHandler;
struct GLFWwindow;
class Shader;

struct NexusConsole {
    std::vector<std::string> Logs;
    char InputBuf[256] = ""; 

    // Храним адрес сокета из main
    zmq::socket_t* NetworkSocket = nullptr;

    void SetSocket(zmq::socket_t* s) { 
        NetworkSocket = s; 
    }

    auto begin() { return Logs.begin(); }
    auto end() { return Logs.end(); }

    void AddLog(const std::string& text) {
        Logs.push_back(text);
    }
};

class NexusGui {
private:
    // Статические данные для шейдера
    static inline float squarePos[2] = { 400.0f, 300.0f };
    static inline float squareScale[2] = { 100.0f, 100.0f };
    static inline float squareRotation = 0.0f;
    static inline float cubeColor[4] = { 1.0f, 0.5f, 0.2f, 1.0f };

    // Указатель на обработчик (решает проблему цикличных инклудов)
    NexusCommandHandler* cmdHandler;

    static NexusConsole console;

    void RenderTransformWindow();
    void RenderPaintWindow();
    void RenderConsoleWindow(GLFWwindow* window);

public:
    NexusGui();
    ~NexusGui(); // Нужно для удаления cmdHandler

    static NexusConsole& GetConsole() { return console; }

    void DrawWidgets(GLFWwindow* window);
    void ApplyToShader(Shader& myShader, float width, float height); 
    void imguiRend();
};






