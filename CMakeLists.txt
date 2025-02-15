cmake_minimum_required(VERSION 3.10)
project(HttpServiceCpp)

set(CMAKE_CXX_STANDARD 17)

# Добавляем исходный файл
add_executable(server ../app/main.cpp)

# Подключаем библиотеки (Crow, yaml-cpp, jwt-cpp)
find_package(yaml-cpp REQUIRED)

# Указываем пути к заголовочным файлам
include_directories(/usr/local/include /opt/homebrew/include)

# Линкуем библиотеки
target_link_libraries(server yaml-cpp pthread)
