cmake_minimum_required(VERSION 3.12.0)
project(frame_capture)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories(v4l2 ${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} 
  main.cc
  v4l2/video_control.cc
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} yaml-cpp)
