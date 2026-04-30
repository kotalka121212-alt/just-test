#version 330 core
out vec4 FragColor;
uniform vec4 ourColor; // Та самая переменная, которую мы заполнили из ImGui

void main() {
    FragColor = ourColor;
}