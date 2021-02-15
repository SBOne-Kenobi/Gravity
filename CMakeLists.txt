cmake_minimum_required(VERSION 3.15)
project(Gravity)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(include)

add_executable(Gravity src/main.cpp
        include/Scene.hpp include/Object.hpp
        src/Engine.cpp include/Engine.hpp
        include/Environment.hpp src/Scene.cpp src/Object.cpp src/RenderComponent.cpp include/RenderComponent.hpp include/Utils.hpp src/EventListener.cpp include/EventListener.hpp)

target_link_libraries(Gravity sfml-graphics sfml-audio)