cmake_minimum_required(VERSION 3.15)
project(Gravity)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(include)

add_executable(Gravity src/main.cpp
        include/engine/Scene.hpp include/engine/Object.hpp
        src/engine/Engine.cpp include/engine/Engine.hpp
        include/Environment.hpp src/engine/Scene.cpp
        src/engine/Object.cpp
        src/components/RenderComponent.cpp include/components/RenderComponent.hpp
        include/engine/Utils.hpp src/engine/EventListener.cpp include/engine/EventListener.hpp
        src/components/PhysicsComponent.cpp include/components/PhysicsComponent.hpp src/engine/Utils.cpp)

target_link_libraries(Gravity sfml-graphics sfml-audio)