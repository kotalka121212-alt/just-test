#include "nexusConsole.h"
#include "NexusCommandHandler.h" // Теперь подключаем здесь
#include "shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Инициализация статического члена
NexusConsole NexusGui::console;

NexusGui::NexusGui() {
    // Создаем обработчик в куче
    cmdHandler = new NexusCommandHandler();
    console.AddLog("--- Nexus Engine UI System Initialized ---");
}

NexusGui::~NexusGui() {
    delete cmdHandler;
}

void NexusGui::DrawWidgets(GLFWwindow* window) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderPaintWindow();
    RenderTransformWindow();
    RenderScaleWindow();
    RenderRotateWindow();
    RenderConsoleWindow(window);
}



void NexusGui::RenderTransformWindow() {
    ImGui::Begin("Nexus Move");
    ImGui::DragFloat3("XYZ Position", squarePos, 0.05f);
    if (ImGui::Button("Reset Pos")) { squarePos[0]=0; squarePos[1]=0; squarePos[2]=0; }
    ImGui::End();
}

void NexusGui::RenderRotateWindow() {
    ImGui::Begin("Nexus Rotate");
    // Слайдер для 3 векторов вращения, как ты и просил
    ImGui::SliderFloat3("Rotation Angles", squareRot, 0.0f, 360.0f);
    if (ImGui::Button("Reset Rotation")) { squareRot[0]=0; squareRot[1]=0; squareRot[2]=0; }
    ImGui::End();
}

void NexusGui::RenderScaleWindow() {
    ImGui::Begin("Nexus Scale");
    ImGui::DragFloat3("XYZ Scale", squareScale, 0.01f);
    if (ImGui::Button("Reset Scale")) { squareScale[0]=1; squareScale[1]=1; squareScale[2]=1; }
    ImGui::End();
}

void NexusGui::RenderPaintWindow() {
    ImGui::Begin("Nexus Painter");
    ImGui::ColorEdit4("Object Color", cubeColor);
    ImGui::End();
}

void NexusGui::RenderConsoleWindow(GLFWwindow* window) {
    // Делегируем отрисовку и логику команд в cmdHandler
    if (cmdHandler) {
        cmdHandler->Draw(window, console);
    }
}

void NexusGui::ApplyToShader(Shader& myShader, float width, float height) {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(squarePos[0], squarePos[1], squarePos[2]));
    
    // Вращение по 3 осям
    model = glm::rotate(model, glm::radians(squareRot[0]), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(squareRot[1]), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(squareRot[2]), glm::vec3(0, 0, 1));
    
    model = glm::scale(model, glm::vec3(squareScale[0], squareScale[1], squareScale[2]));

    glUseProgram(myShader.ID);
    glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(glGetUniformLocation(myShader.ID, "ourColor"), 1, cubeColor);
}

void NexusGui::imguiRend() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}