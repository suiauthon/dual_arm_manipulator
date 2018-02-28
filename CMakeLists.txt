cmake_minimum_required(VERSION 2.8.3)
project(dual_arm_manipulator)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    rospy
    roslib
    rospack
    std_msgs
    dynamic_reconfigure
    dynamixel_msgs
)

find_package(cmake_modules REQUIRED)
    
catkin_package(
   INCLUDE_DIRS include
   LIBRARIES dual_arm_manipulator
   CATKIN_DEPENDS roscpp rospy roslib rospack dynamixel_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(tf2 src/Tf2.cpp)
target_link_libraries(tf2 ${catkin_LIBRARIES})

add_library(DualArmManipulatorDirectKinematics src/DualArmManipulatorDirectKinematics.cpp)
target_link_libraries(DualArmManipulatorDirectKinematics ${catkin_LIBRARIES} yaml-cpp)

add_library(DualArmManipulatorInverseKinematics src/DualArmManipulatorInverseKinematics.cpp)
target_link_libraries(DualArmManipulatorInverseKinematics DualArmManipulatorDirectKinematics ${catkin_LIBRARIES} yaml-cpp)

add_executable(dual_arm_manipulator_control_node src/dual_arm_manipulator_control.cpp)
target_link_libraries(dual_arm_manipulator_control_node DualArmManipulatorDirectKinematics DualArmManipulatorInverseKinematics ${catkin_LIBRARIES} yaml-cpp tf2)