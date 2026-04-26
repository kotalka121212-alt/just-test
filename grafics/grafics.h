#pragma once

#include "opengl.h"


class Window{

    private:

    GLFWwindow* mWindow;


    public:

    Window(size_t height, size_t width, string name ){

	mWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	if (!mWindow) {
		throw std::runtime_error("couldnt make window");
	}
	glfwMakeContextCurrent(mWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("couldnt initialize glad");
    }

    }

    ~Window() { glfwDestroyWindow(mWindow); }

       void loop(){
        
        while (!glfwWindowShouldClose(mWindow)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mWindow);
        glfwPollEvents();

    }
}
 









};
    




