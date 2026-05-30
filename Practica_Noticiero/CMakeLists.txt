cmake_minimum_required(VERSION 3.10)
project(GeneradorNoticias VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include_directories(include)

set(SOURCES
	    src/main.cpp
	    src/SistemaNoticias.cpp
	    src/Editor.cpp
	    src/Lector.cpp
)

add_executable(sistema_noticias ${SOURCES})
target_link_libraries(sistema_noticias PRIVATE Threads::Threads)
