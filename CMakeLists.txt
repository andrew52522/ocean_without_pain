cmake_minimum_required(VERSION 3.14)
project(OceanSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- НАЧАЛО БЛОКА SFML ---

# Укажи здесь путь к папке, куда ты распаковал SFML

# Разработчик! измени путь до библиотеки SFML здесь в set() внизу
set(SFML_DIR "C:/Users/User/Documents/SFML-2.6.1/lib/cmake/SFML")

# Находим пакет SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Автоматически находим все исходные файлы .cpp в папке src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Создаём исполняемый файл из всех найденных исходников
add_executable(ocean_simulation ${SOURCES})

# 2. ПОДКЛЮЧАЕМ БИБЛИОТЕКИ! Это самая важная часть.
target_link_libraries(ocean_simulation PRIVATE sfml-graphics)
