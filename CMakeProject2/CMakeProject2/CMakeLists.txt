cmake_minimum_required(VERSION 3.10)
project(CMakeProject2)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем директории с заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR})

# Добавляем исполняемый файл, указывая, какие файлы использовать
add_executable(CMakeProject2 CMakeProject2.cpp)

# Подключаем библиотеку Winsock2 если это Windows
if(WIN32)
    target_link_libraries(CMakeProject2 Ws2_32)
endif()
