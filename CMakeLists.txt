cmake_minimum_required(VERSION 2.8.3)
project(yolo_test)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  darknet_ros
  darknet_ros_msgs
  message_generation
  roscpp
  std_msgs
)
catkin_package(
  INCLUDE_DIRS
  include
  LIBRARIES yolo_test
  CATKIN_DEPENDS darknet_ros message_generation roscpp std_msgs
  )

set(PROJECT_LIB_FILES
    src/yolo.cpp
)

include_directories(
  INCLUDE_DIRS
  include
  ${catkin_INCLUDE_DIRS}
)
add_library(${PROJECT_NAME}_lib
${PROJECT_LIB_FILES})

add_executable(yolo_test src/main.cpp)

add_dependencies(yolo_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(yolo_test
  ${PROJECT_NAME}_lib
  ${catkin_LIBRARIES}
)