cmake_minimum_required(VERSION 3.21)
project(477_hw1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(raytracer raytracer.cpp Vector.h Camera.cpp Camera.h
        default_files/ppm.h default_files/ppm.cpp default_files/tinyxml2.h default_files/tinyxml2.cpp Ray.cpp Ray.h Scene.cpp Scene.h Object.cpp Object.h helpers.h)

