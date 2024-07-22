cmake_minimum_required(VERSION 3.10)
project(CMakeProject1)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем директории с заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR})

# Добавляем исполняемый файл, указывая, какие файлы использовать
add_executable(CMakeProject1 CMakeProject1.cpp)

# Поиск и подключение библиотеки Winsock2
# Проверяем наличие компилятора для Windows
# Проверяем наличие компилятора для Windows
if(WIN32)
    # Добавляем библиотеку Winsock2
    target_link_libraries(CMakeProject1 Ws2_32)
endif()
