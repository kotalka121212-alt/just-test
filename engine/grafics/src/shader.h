#pragma once
#include "inc_gr.h"

#include <imgui.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath) {
        string vertexCode, fragmentCode;
        ifstream vShaderFile, fShaderFile;
        
        vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (ifstream::failure& e) {
            cerr << "ERROR::SHADER::FILE_NOT_READ: " << e.what() << endl;
        }

        if (vertexCode.empty() || fragmentCode.empty()) {
            cerr << "--- КРИТИЧЕСКАЯ ОШИБКА: Шейдеры пустые! ---" << endl;
            cerr << "Ищу здесь: " << std::filesystem::current_path() << endl;
            return;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[1024];

        // Компиляция Вершинного шейдера
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
            cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        }

        // Компиляция Фрагментного шейдера
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
            cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
        }

        // Создание программы и ЛИНКОВКА (Вот это самое важное!)
        ID = glCreateProgram();
        glAttachShader(ID, vertex);   // ПРИКРЕПЛЯЕМ ВЕРШИННЫЙ
        glAttachShader(ID, fragment); // ПРИКРЕПЛЯЕМ ФРАГМЕНТНЫЙ
        glLinkProgram(ID);            // СВЯЗЫВАЕМ ИХ ВМЕСТЕ

        // Проверка ошибок линковки
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 1024, NULL, infoLog);
            cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
        }

        // Удаляем временные шейдеры, они уже внутри программы
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() { 
        glUseProgram(ID); 
    }
};


