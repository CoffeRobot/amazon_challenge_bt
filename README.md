# README #
ROS package for Behavior Tree leaf nodes (Actions and Conditions).
The package is based on the actionlib library (http://wiki.ros.org/actionlib) 


### What is this repository for? ###

This package contains the ros nodes executing actions and conditions. These nodes are clients in the actionlib library. 

### How do I get set up? ###

Download the repository and build it (catkin_make).
To gain familarity on how this works I wrote one example in C++ and one in python.
    
###Example in C++ ###
Run the Server

    rosrun bt_action Action 

Run the Client

    rosrun bt_action ActionClient 

Press: 1 to start the execution; 2 to halt the execution and 3 to terminate the program







### Contribution guidelines ###


### Who do I talk to? ###

Michele