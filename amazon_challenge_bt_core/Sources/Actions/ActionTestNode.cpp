#include "ActionTestNode.h"



using namespace BT;

enum Status {RUNNING,SUCCESS, FAILURE};



ActionTestNode::ActionTestNode(std::string Name) : ActionNode::ActionNode(Name)
{
    Type = Action;
    // Thread start
    Thread = boost::thread(&ActionTestNode::Exec, this);




}

ActionTestNode::~ActionTestNode() {}

void ActionTestNode::Exec()
{


    //bool hasReturned = false;
	  // create the action client
	  // true causes the client to spin its own thread
    ROS_INFO("Waiting For the Acutator moveforward to start");

      actionlib::SimpleActionClient<bt_actions::BTAction> ac("moveforward", true);

      ac.waitForServer(); //will wait for infinite time until the server starts
      bt_actions::BTGoal goal;
      node_result.status = RUNNING;//
    while(true)
    {
        // Waiting for a tick to come
        Semaphore.Wait();

        if(ReadState() == Exit)
        {
            // The behavior tree is going to be destroied
            return;
        }

        // Running state
        SetNodeState(Running);
        std::cout << Name << " returning " << Running << "!" << std::endl;
        node_result.status = RUNNING;
        // Perform action...

                    ROS_INFO("I am running the request to ACTION");
                    ac.sendGoal(goal);
                    //ac.waitForResult(ros::Duration(30.0));
            do{
                node_result = *(ac.getResult());//checking the result

                    } while(node_result.status == RUNNING && ReadState() == Running);
            ROS_INFO("The Server Has Replied");

                    std::cout << Name << " RETURNING " << node_result.status << "!" << std::endl;

        if(ReadState() == Exit)
        {
            // The behavior tree is going to be destroied
            return;
        }


        if (node_result.status == SUCCESS)
        {
            // trying to set the outcome state:
            if (WriteState(Success) != true)
            {
                // meanwhile, my father halted me!
                std::cout << Name << " Halted!" << std::endl;
                ROS_INFO("I am cancelling the request");
                ac.cancelGoal();
                // Resetting the state
                WriteState(Idle);
                continue;
            }

            std::cout << Name << " returning Success " << Success << "!" << std::endl;
        }
        else if( node_result.status == FAILURE)
        {
            // trying to set the outcome state:
            if (WriteState(Failure) != true)
            {
                // meanwhile, my father halted me!
                std::cout << Name << " Halted!" << std::endl;
                ROS_INFO("I am cancelling the request");
                ac.cancelGoal();
                // Resetting the state
                WriteState(Idle);
                continue;
            }

            std::cout << Name << " returning Failure" << Failure << "!" << std::endl;
        }else{

            std::cout << Name << " Halted!" << std::endl;
            ROS_INFO("I am cancelling the request");
            ac.cancelGoal();
            // Resetting the state
            WriteState(Idle);
            continue;

            std::cout << Name << " returning NOTHING (HALTED)" << Failure << "!" << std::endl;
        }


            std::cout << Name << " returning " << Success << "!" << std::endl;


        // Synchronization
        // (my father is telling me that it has read my new state)
        Semaphore.Wait();

        if(ReadState() == Exit)
        {
            // The behavior tree is going to be destroied
            return;
        }

        // Resetting the state
        WriteState(Idle);
    }
}

bool ActionTestNode::Halt()
{

	  //actionlib::SimpleActionClient<bt_actions::BTAction> ac("action", true);
        ROS_INFO("I am Halting the client");
	//ac.cancelGoal();
    // Lock acquistion
    boost::lock_guard<boost::mutex> LockGuard(StateMutex);

    // Checking for "Running" correctness
    if (State != Running)
    {
        return false;
    }

    State = Halted;
    return true;
}
