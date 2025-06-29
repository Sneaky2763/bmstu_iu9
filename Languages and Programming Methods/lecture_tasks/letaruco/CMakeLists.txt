cmake_minimum_required(VERSION 3.5)
project(aruco_camera)

find_package(OpenCV REQUIRED)

add_executable(aruco_camera aruco_camera.cpp)
target_link_libraries(aruco_camera ${OpenCV_LIBS})
