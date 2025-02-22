cmake_minimum_required(VERSION 3.10)
project(HttpServiceCpp)

set(CMAKE_CXX_STANDARD 17)

# Подключаем Conan
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
if(EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
    include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
endif()

# Добавляем исходный файл
add_executable(server ../app/main.cpp)

# Подключаем библиотеки (Crow, yaml-cpp, jwt-cpp)
find_package(yaml-cpp REQUIRED)
find_package(jwt-cpp REQUIRED)
find_package(Crow REQUIRED)
find_package(picojson REQUIRED)

# Указываем пути к заголовочным файлам
#include_directories(/usr/local/include /opt/homebrew/include)


# Линкуем библиотеки
target_link_libraries(server yaml-cpp::yaml-cpp jwt-cpp::jwt-cpp Crow::Crow picojson::picojson)

# Указываем путь для выходного файла
set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})