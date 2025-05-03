cmake_minimum_required(VERSION 3.7)

project(AsteroidShooter)

file(GLOB SOURCE_FILES "src/*.cpp")


find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image sharpyuv jxl yuv spdlog fmt)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

#cmake_minimum_required(VERSION 3.7)

#project(AsteroidShooter)

#file(GLOB SOURCE_FILES "src/*.cpp")

#add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)

#include_directories(${sdl2image_include_dir})
#include_directories(${sdl2_include_dirs})

#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})