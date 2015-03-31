# README #
ROS package for Behavior Tree leaf nodes (Actions and Conditions).
The package is based on the actionlib library (http://wiki.ros.org/actionlib) 


### What is this repository for? ###

This package contains the ros nodes executing actions and conditions. These nodes are clients in the actionlib library. 

### How do I get set up? ###

Download the repository and build it (catkin_make).

The file src/example_action_server.cpp is a template on how the your ROS node should look like it it performs and action (it is an action in the Behavior Tree).
Your action is the Server and does stuff. The Behavior Tree is the Client and tells to all the Server which ones have to start (TICK) and which have to stop (HALT).

Edit in example action 

void executeCB(const bt_actions::BTGoalConstPtr &goal)
	  {

	    // publish info to the console for the user
	    ROS_INFO("Starting Action");

	    // start executing the action
	    while(/*YOUR CONDITION*/)
	    {
	      // check that preempt has not been requested by the client
	      if (as_.isPreemptRequested() || !ros::ok())
	      {
		ROS_INFO("Action Halted");


	 /*
		    HERE THE CODE TO EXECUTE WHEN THE  BEHAVIOR TREE DOES HALT THE ACTION
	*/


		// set the action state to preempted
		as_.setPreempted();
		success = false;
		break;
	      }


	      ROS_INFO("Executing Action");
	/*
		  HERE THE CODE TO EXECUTE AS LONG AS THE BEHAVIOR TREE DOES NOT HALT THE ACTION
	*/

	 //If the action succeeded
	      setStatus(SUCCESS);
	//If the action Failed
	      setStatus(FAILURE);

	   }






To gain familarity on how this works I wrote one example in C++ and one in python.
    
###Example in C++ ###
Run the Server

    rosrun bt_action Action 

Run the Client

    rosrun bt_action ActionClient 

Press: 1 to start the execution; 2 to halt the execution and 3 to terminate the program.







### Contribution guidelines ###


### Who do I talk to? ###

Michele