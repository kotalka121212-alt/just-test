#pragma once

#include "opengl.h"
#include <zmq.hpp>
#include <Mesh.h>

class Window {
private:
    GLFWwindow* mWindow;


public:
    float width = 800.0f; 
    float height = 600.0f;


    Window(size_t height, size_t width, string name) {
        // GLFW принимает width, height
        mWindow = glfwCreateWindow((int)width, (int)height, name.c_str(), nullptr, nullptr);
        if (!mWindow) {
            throw std::runtime_error("couldnt make window");
        }
        glfwMakeContextCurrent(mWindow);
        
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("couldnt initialize glad");
        }

        glEnable(GL_DEPTH_TEST);



        // 1. Создаем контекст
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO(); (void)io;

// 2. Настраиваем стиль (темная тема — база)
ImGui::StyleColorsDark();

// 3. Подключаем бэкенды к твоему окну
ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
ImGui_ImplOpenGL3_Init("#version 130"); // Версия шейдеров


    }


void close() {
    glfwSetWindowShouldClose(mWindow, true);
}


    ~Window() {
        if (mWindow) glfwDestroyWindow(mWindow);
    }

    bool shouldClose() { return glfwWindowShouldClose(mWindow); }
    void swapBuffers() { glfwSwapBuffers(mWindow); }

    // Теперь вся логика шейдеров и буферов перенесена сюда
    void loop() {
        // 1. Инициализация шейдеров
        Shader myShader("../engine/grafics/source/vertex.vert", "../engine/grafics/source/fragment.frag");

        // 2. Данные геометрии (квадрат)
        float vertices[] = {
             0.5f,  0.5f, 0.0f, // право верх
             0.5f, -0.5f, 0.0f, // право низ
            -0.5f, -0.5f, 0.0f, // лево низ
            -0.5f,  0.5f, 0.0f  // лево верх
        };
        unsigned int indices[] = {
            0, 1, 3, // первый треугольник
            1, 2, 3  // второй треугольник
        };

        Mesh square(vertices, sizeof(vertices), indices, sizeof(indices));

        NexusGui ui;

zmq::context_t context(1);
zmq::socket_t publisher(context, zmq::socket_type::pub); // Используем socket_type
publisher.bind("tcp://*:5555");



ui.GetConsole().SetSocket(&publisher);

        // 4. Основной цикл
        while (!glfwWindowShouldClose(mWindow)) {
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

ui.DrawWidgets(mWindow);




myShader.use();

ui.ApplyToShader(myShader,width,height);



square.Draw();

// 4. РЕНДЕР (Отрисовка)
            ui.imguiRend();
            swapBuffers();
            glfwPollEvents();
        }
    }










    void setIcon(const string& path) {
        GLFWimage image;
        int channels;
        unsigned char* pixels = stbi_load(path.c_str(), &image.width, &image.height, &channels, STBI_rgb_alpha);
        if (pixels) {
            image.pixels = pixels;
            glfwSetWindowIcon(mWindow, 1, &image);
            stbi_image_free(pixels);
        }
    }
};


