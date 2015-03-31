# README #
ROS package for Behavior Tree's leaf nodes (Actions and Conditions).
The package is based on the actionlib library (http://wiki.ros.org/actionlib) 


### What is this repository for? ###

This package contains the ros nodes executing actions and conditions. These nodes are clients in the actionlib library. 

### How do I get set up? ###

Download the repository and build it (catkin_make).

###Set up an Behavior Tree's action in C++
The file src/example_action_server.cpp is a template on how the your ROS node should look like it it performs and action (it is an action in the Behavior Tree).
Your action is the Server and does stuff. The Behavior Tree is the Client and tells to all the Server which ones have to start (TICK) and which have to stop (HALT).

Edit in example_action_server.cpp the executeCB procedure, adding your code to execute when the node is TICKED and when is HALTED. If the action is finished the node should send the return status (SUCCESS/FAILURE) calling setStatus(SUCCESS/FAILURE).

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




###Set up an Behavior Tree's condition in C++
The procedure is similar to the one above.
The file src/example_condition_server.cpp is a template on how the your ROS node should look like when it checks a condition (it is a condition in the Behavior Tree).
Your condition is the Server and checks stuff. The Behavior Tree is the Client and tells to all the Server which ones have to start (TICK) and which have to stop (HALT).

Edit in example_condition_server.cpp the executeCB procedure, adding your code to execute when the node is TICKED (it is never halted). If the condition is satisfied then the condition returns the status setStatus(SUCCESS). If the condition is not satisfied then the condition returns the status setStatus(SUCCESS). 
IMPORTANT! A condition is supposed to reply very fast. If it takes too much time (apporx more that  seconds), the node has to be defined as an action.


		  void executeCB(const bt_actions::BTGoalConstPtr &goal)
		  {
		    if(/*condition satisfied*/)
                    {
		        setStatus(SUCCESS);
		    }else{
		        setStatus(FAILURE);
		    }
		  }



###Set up an Behavior Tree's action in python
The file src/example_action_server.py is a template on how the your ROS node should look like it it performs and action (it is an action in the Behavior Tree).
Your action is the Server and does stuff. The Behavior Tree is the Client and tells to all the Server which ones have to start (TICK) and which have to stop (HALT).

Edit in example_action_server.py the execute_cb procedure, adding your code to execute when the node is TICKED and when is HALTED. If the action is finished the node should send the return status (SUCCESS/FAILURE) calling setStatus(SUCCESS/FAILURE).





def execute_cb(self, goal):
		    # publish info to the console for the user
		    rospy.loginfo('Starting Action')
		    
		    # start executing the action
		    while #your condition:
		      # check that preempt has not been requested by the client
		      if self._as.is_preempt_requested():
			#HERE THE CODE TO EXECUTE WHEN THE  BEHAVIOR TREE DOES HALT THE ACTION
			rospy.loginfo('Action Halted')
			self._as.set_preempted()
			success = False
			break

		      	rospy.loginfo('Executing Action')      
		      	#HERE THE CODE TO EXECUTE AS LONG AS THE BEHAVIOR TREE DOES NOT HALT THE ACTION
		      
			#IF THE ACTION HAS SUCCEEDED
			self.set_status('SUCCESS')
			#IF THE ACTION HAS FAILED
			self.set_status('FAILURE')




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