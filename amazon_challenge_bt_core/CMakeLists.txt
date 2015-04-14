cmake_minimum_required(VERSION 2.8.3)
project(amazon_challenge_bt_core)

# Needed for using threads

#set(CMAKE_PREFIX_PATH ~/naoqi/naoqi-sdk-1.14.5-linux64)
#set(LD_LIBRARY_PATH:~/naoqi/naoqi-sdk-1.14.5-linux64/lib)

#set(ALPROXIES_DIR ~/naoqi/naoqi-sdk-1.14.5-linux64/share/cmake/alproxies)
#INCLUDE_DIRECTORIES(${ALPROXIES_DIR})

#find_package(catkin REQUIRED COMPONENTS 
#roscpp
#rospy
#std_msgs
#genmsg
#)


find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  amazon_challenge_bt_actions
  message_generation
  roscpp
  rospy
  std_msgs
)

add_action_files(
  DIRECTORY action
  FILES BT.action
)


generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs  # Or other packages containing msgs
)


#messages
#generate_messages(
 # DEPENDENCIES
 # std_msgs
#)
# NAO
#find_package(ALCOMMON  REQUIRED)
#find_package(ALPROXIES REQUIRED)
#find_package(ALVISION  REQUIRED)
#find_package(ALVALUE   REQUIRED)

#catkin_package(CATKIN_DEPENDS roscpp std_msgs)



catkin_package(
  CATKIN_DEPENDS actionlib_msgs
  INCLUDE_DIRS include
)

INCLUDE_DIRECTORIES(${catkin_INCLUDE_DIRS} include)



file(GLOB_RECURSE BTLibrary src/*.cpp)

add_executable(tree src/main.cpp ${BTLibrary})
#target_link_libraries(tree ${catkin_LIBRARIES} ${ALPROXIES_LIBRARIES} ${ALVALUE_LIBRARIES})
add_dependencies(tree amazon_challenge_bt_actions_generate_messages_cpp)
target_link_libraries(tree ${catkin_LIBRARIES})

#add_executable(add_two_ints_server ${PROJECT_SOURCE_DIR}/src/add_two_ints_server.cpp)
#target_link_libraries(add_two_ints_server ${catkin_LIBRARIES})
#add_dependencies(add_two_ints_server beginner_tutorials_generate_message_cpp)

#add_executable(add_two_ints_client ${PROJECT_SOURCE_DIR}/src/add_two_ints_client.cpp)
#target_link_libraries(add_two_ints_client ${catkin_LIBRARIES})
#add_dependencies(add_two_ints_client beginner_tutorials_generate_message_cpp)
