cmake_minimum_required(VERSION 3.14) # Минимальная требуемая версия CMake
project(03_week) # Необходим для инициализации cmake

set(CMAKE_CXX_STANDARD 20) # Версия стандарта C++
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Гарантирует использование указанной версии стандарта

set(EXAMPLES_DIR examples) # Определим переменную с именем директории
set(TASKS_DIR tasks)

add_subdirectory(tasks)

# Создать исполняемый файл для каждого примера
if (BUILD_EXAMPLES_03_WEEK)
    add_example(struct_examples ${EXAMPLES_DIR}/struct_examples.cpp)
    add_example(union_examples ${EXAMPLES_DIR}/union_examples.cpp)
    add_example(vector_examples ${EXAMPLES_DIR}/vector_examples.cpp)
endif()