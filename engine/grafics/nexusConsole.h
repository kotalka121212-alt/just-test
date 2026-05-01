

#pragma once
#include "inc_gr.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct NexusConsole {
    std::vector<std::string> Logs;
    char InputBuf[256] = ""; // Буфер для ввода текста

    // Итераторы для удобного обхода (то, что ты просил)
    auto begin() { return Logs.begin(); }
    auto end() { return Logs.end(); }

    void AddLog(const std::string& text) {
        Logs.push_back(text);
    }
};


class NexusGui {

    private:
        static inline float squarePos[2] = { 400.0f, 300.0f }; // Центр экрана
        static inline float squareScale[2] = { 100.0f, 100.0f }; // Заметный размер
        static inline float squareRotation = 0.0f;         // Поворот (в градусах)
        static inline float cubeColor[4] = { 1.0f, 0.5f, 0.2f, 1.0f };

        static NexusConsole console;

    void RenderTransformWindow();
    void RenderPaintWindow();
    void RenderConsoleWindow(GLFWwindow* window);

public:
    NexusGui();
    void DrawWidgets(GLFWwindow* window);
    void ApplyToShader(class Shader& myShader, float width, float height); 
    void imguiRend();
};







