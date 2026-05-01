#pragma once

#include "opengl.h"
#include <zmq.hpp>

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

        // 3. Создание буферов в GPU
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Настройка атрибутов (Position)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Разблокируем VAO
        glBindVertexArray(0);



        NexusGui ui;

zmq::context_t context(1);
zmq::socket_t publisher(context, zmq::socket_type::pub); // Используем socket_type
publisher.bind("tcp://*:5557");



ui.GetConsole().SetSocket(&publisher);

        // 4. Основной цикл
        while (!glfwWindowShouldClose(mWindow)) {
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

ui.DrawWidgets(mWindow);




myShader.use();

ui.ApplyToShader(myShader,width,height);



glBindVertexArray(VAO);



glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


// 4. РЕНДЕР (Отрисовка)


            ui.imguiRend();

            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }

        // Очистка памяти GPU после выхода из цикла
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
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


