#pragma once

#include "opengl.h"


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


        static float squarePos[2] = { 400.0f, 300.0f }; // Центр экрана
        static float squareScale[2] = { 100.0f, 100.0f }; // Заметный размер
        static float squareRotation = 0.0f;         // Поворот (в градусах)
        static float cubeColor[4] = { 1.0f, 0.5f, 0.2f, 1.0f };



        // 4. Основной цикл
        while (!glfwWindowShouldClose(mWindow)) {
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();



// --- ВИДЖЕТ №1: Управление цветом ---
ImGui::Begin("Nexus Paint"); 
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Color Settings");
    ImGui::ColorEdit4("Square Color", cubeColor); 
ImGui::End();

// --- ВИДЖЕТ №2: Преобразования (Трансформы) ---
ImGui::Begin("Nexus Transform");
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "Geometry Controls");
    
    ImGui::Separator();
    
    // Двигаем (в пикселях, если добавил ortho)
    ImGui::DragFloat2("Position (X,Y)", squarePos, 1.0f);
    
    // Масштабируем (отдельно ширину и высоту)
    ImGui::DragFloat2("Scale (W,H)", squareScale, 1.0f, 1.0f, 500.0f);
    
    // Вращаем
    ImGui::SliderFloat("Rotation", &squareRotation, 0.0f, 360.0f);
    
    if (ImGui::Button("Reset Transform")) {
        squarePos[0] = 400.0f; squarePos[1] = 300.0f;
        squareScale[0] = 100.0f; squareScale[1] = 100.0f;
        squareRotation = 0.0f;
    }
ImGui::End();



            // Очистка экрана


            // Рендеринг


myShader.use();

// 2. Считаем матрицу ПРОЕКЦИИ (делаем мир плоским 800x600)
// Теперь 0,0 — это левый верхний угол, а 800,600 — правый нижний
glm::mat4 projection = glm::ortho(0.0f, width, height, 0.0f, -100.0f, 100.0f);
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

glBindVertexArray(VAO);



glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


// 4. РЕНДЕР (Отрисовка)
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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


