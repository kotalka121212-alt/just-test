# Добавляем библиотеку
add_library(mysources STATIC 
myiterator.cpp myiterator.h

)




# Указываем, где искать заголовочные файлы этой библиотеки
# PUBLIC означает: все, кто линкует MyLib, автоматически видят папку ${CMAKE_CURRENT_SOURCE_DIR}
target_include_directories(mysources PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mysources PRIVATE linker)