#include "nexusConsole.h"
#include "shader.h" // Теперь здесь это безопасно
#include <glm/gtc/type_ptr.hpp>

NexusConsole NexusGui::console;

NexusGui::NexusGui() {
    console.AddLog("--- Nexus Engine UI System Initialized ---");
}

// Реализация метода здесь
void NexusGui::DrawWidgets(GLFWwindow* window) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Запускаем наши подметоды[cite: 4, 9]
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
    ImGui::Begin("Nexus System Console");
    
    // 1. Область вывода логов
    float footer_height = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height), true);
    
    for (auto it = console.begin(); it != console.end(); ++it) {
        ImGui::TextUnformatted(it->c_str());
    }

    // Автопрокрутка вниз
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();

    ImGui::Separator();

    // 2. Поле ввода команд
    // Используем флаг EnterReturnsTrue, чтобы код срабатывал только при нажатии Enter
    if (ImGui::InputText("##cmd", console.InputBuf, IM_ARRAYSIZE(console.InputBuf), ImGuiInputTextFlags_EnterReturnsTrue)) {
        std::string cmd(console.InputBuf);

        if (cmd.length() > 0) {
            // Обработка команды "say "
            if (cmd.substr(0, 4) == "say ") {
                std::string payload = "[Nexus]: " + cmd.substr(4);
                
                // Проверяем, что сокет был передан через SetSocket в Window::loop
                if (console.NetworkSocket) {
                    // Отправляем сообщение в твой клиент (5555 порт)
                    console.NetworkSocket->send(zmq::buffer(payload), zmq::send_flags::none);
                }
                
                console.AddLog(payload); // Добавляем в локальный лог
            } 
            else {
                // Если это не "say", просто логируем ввод
                console.AddLog("> " + cmd);
            }
        }

        // Очищаем буфер после нажатия Enter
        console.InputBuf[0] = '\0';
        
        // Возвращаем фокус на поле ввода
        ImGui::SetKeyboardFocusHere(-1);
    }

    ImGui::End();
}
 void NexusGui::ApplyToShader(Shader& myShader, float width, float height){
    
// 2. Считаем матрицу ПРОЕКЦИИ (делаем мир плоским 800x600)
// Теперь 0,0 — это левый верхний угол, а 800,600 — правый нижний
glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -100.0f, 100.0f);
int projLoc = glGetUniformLocation(myShader.ID, "projection");
glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

// 3. Считаем матрицу МОДЕЛИ (где конкретно наш квадрат)
glm::mat4 model = glm::mat4(1.0f);
model = glm::translate(model, glm::vec3(squarePos[0], squarePos[1], 0.0f)); // Смещение
model = glm::rotate(model, glm::radians(squareRotation), glm::vec3(0, 0, 1)); // Поворот
model = glm::scale(model, glm::vec3(squareScale[0], squareScale[1], 1.0f));   // Размер

int modelLoc = glGetUniformLocation(myShader.ID, "model");
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

// 4. Закидываем цвет (как раньше)
int colorLoc = glGetUniformLocation(myShader.ID, "ourColor");
glUniform4fv(colorLoc, 1, cubeColor);

}

    
void NexusGui::imguiRend(){
        ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}