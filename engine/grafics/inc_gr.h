#pragma once
//*stl ->
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <vector>


//*opengl ->

#include <glad/include/glad/glad.h>  
#include <GLFW/glfw3.h>   

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//grafics ->

#include <opengl.h>



//*boost ->

#include <boost/algorithm/string.hpp> //* для обработки строк
#include <boost/lexical_cast.hpp>   //* для конвертации
#include <boost/property_tree/json_parser.hpp> //* если нужен второй JSON парсер
#include <boost/random.hpp>//* нормальный рандом
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>


//*nn ->

#include "vector.h"
#include "matrix.h"




#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include <stb_image.h>

using namespace std;