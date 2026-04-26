#pragma once

#include "opengl.h"


class Window {
private:
    GLFWwindow* mWindow;

public:
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
    }

    ~Window() {
        if (mWindow) glfwDestroyWindow(mWindow);
    }

    bool shouldClose() { return glfwWindowShouldClose(mWindow); }
    void swapBuffers() { glfwSwapBuffers(mWindow); }

    // Теперь вся логика шейдеров и буферов перенесена сюда
    void loop() {
        // 1. Инициализация шейдеров
        Shader myShader("../grafics/source/vertex.vert", "../grafics/source/fragment.frag");

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

        // 4. Основной цикл
        while (!glfwWindowShouldClose(mWindow)) {
            // Очистка экрана
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Рендеринг
            myShader.use();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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


