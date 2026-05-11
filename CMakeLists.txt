# Минимальная требуемая версия CMake (почти всегда 3.10+ для новых проектов)
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(just-test VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(USB_LIB_PATH "G:/progects_c++/mingw/ucrt64/lib/libusb-1.0.dll.a")

set(BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(BUILD_STATIC ON CACHE BOOL "" FORCE)

# Отключаем всё, что генерирует лишние файлы и проверки
set(ZMQ_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ENABLE_CPACK OFF CACHE BOOL "" FORCE)

add_subdirectory(engine)


# Создаем исполняемый файл (exe) из исходника main.cpp
add_executable(my_app main.cpp)
add_executable(test_client test_client.cpp)

link_directories("G:/progects_c++/mingw/ucrt64/lib")



add_executable(mobile 
    nexus-mobile/mobile.cpp

)

target_include_directories(mobile PRIVATE 
    "engine/source_libs/libs2/masters/libnfc-master/include"

)


add_library(sub_lib INTERFACE)


target_link_libraries(sub_lib INTERFACE 
main_lib grafics inc_lib 


)


target_link_libraries(test_client PRIVATE sub_lib)
target_link_libraries(my_app PRIVATE sub_lib)


add_custom_command(TARGET mobile POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_BINARY_DIR}/engine/source_libs/libs2/masters/libnfc-master/libnfc/libnfc.dll"
    $<TARGET_FILE_DIR:mobile>
)

target_link_libraries(mobile PRIVATE sub_lib
    nfc 
    nfc 
    "${USB_LIB_PATH}"
    mfcuk mfoc

)

