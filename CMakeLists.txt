# Минимальная требуемая версия CMake (почти всегда 3.10+ для новых проектов)
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(just-test VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(src)


# Создаем исполняемый файл (exe) из исходника main.cpp
add_executable(my_app main.cpp)




target_link_libraries(my_app PRIVATE 
linker

)