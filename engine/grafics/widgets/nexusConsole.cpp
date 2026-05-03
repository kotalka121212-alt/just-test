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

    RenderTransformWindow();
    RenderPaintWindow();
    RenderConsoleWindow(window);
}

void NexusGui::RenderTransformWindow() {
    ImGui::Begin("Nexus Transform");
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "Geometry Controls");
    ImGui::DragFloat2("Position", squarePos, 1.0f);
    ImGui::DragFloat2("Scale", squareScale, 1.0f, 1.0f, 500.0f);
    ImGui::SliderFloat("Rotation", &squareRotation, 0.0f, 360.0f);
    ImGui::End();
}

void NexusGui::RenderPaintWindow() {
    ImGui::Begin("Nexus Paint");
    ImGui::ColorEdit4("Square Color", cubeColor);
    ImGui::End();
}

void NexusGui::RenderConsoleWindow(GLFWwindow* window) {
    // Делегируем отрисовку и логику команд в cmdHandler
    if (cmdHandler) {
        cmdHandler->Draw(window, console);
    }
}

void NexusGui::ApplyToShader(Shader& myShader, float width, float height) {
    // 2. Матрица ПРОЕКЦИИ
    glm::mat4 projection = glm::ortho(0.0f, width, height, 0.0f, -100.0f, 100.0f);
    int projLoc = glGetUniformLocation(myShader.ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // 3. Матрица МОДЕЛИ
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(squarePos[0], squarePos[1], 0.0f));
    model = glm::rotate(model, glm::radians(squareRotation), glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(squareScale[0], squareScale[1], 1.0f));

    int modelLoc = glGetUniformLocation(myShader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // 4. Цвет
    int colorLoc = glGetUniformLocation(myShader.ID, "ourColor");
    glUniform4fv(colorLoc, 1, cubeColor);
}

void NexusGui::imguiRend() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}