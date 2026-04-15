# Добавляем библиотеку
add_library(MyLib STATIC data.cpp data.h)

# Указываем, где искать заголовочные файлы этой библиотеки
# PUBLIC означает: все, кто линкует MyLib, автоматически видят папку ${CMAKE_CURRENT_SOURCE_DIR}
target_include_directories(MyLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})