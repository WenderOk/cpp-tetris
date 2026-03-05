cmake_minimum_required(VERSION 3.15)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

# Собираем все .cpp файлы из src
file(GLOB SOURCES 
    src/*.cpp
)

# Создаем исполняемый файл
add_executable(Tetris ${SOURCES})

# Подключаем заголовочные файлы
target_include_directories(Tetris PRIVATE 
    src/
)

