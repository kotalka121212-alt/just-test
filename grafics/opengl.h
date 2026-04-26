#pragma once
#include <inc_gr.h>

class GLFW{

public:

GLFW(){
	if (!glfwInit())
	{
		throw std::runtime_error("couldn't initialize glfw!");
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

~GLFW(){
    glfwTerminate();
}




};
