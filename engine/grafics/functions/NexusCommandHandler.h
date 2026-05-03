#pragma once
#include "inc_gr.h"
#include "imgui.h" 


class NexusConsole; 
struct GLFWwindow; // Если GLFW тоже ругается

class NexusCommandHandler {
public:
    NexusCommandHandler();
    
    // В прототипах функций используем ссылку (&), это работает без полного хедера
    void Process(const std::string& input, NexusConsole& console);
    void Draw(GLFWwindow* window, NexusConsole& console);

private:
    std::map<std::string, std::function<void(const std::vector<std::string>&)>> commands;
    std::vector<std::string> split(const std::string& s);
};