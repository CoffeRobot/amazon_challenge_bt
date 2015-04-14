#ifndef ROSACTION_H
#define ROSACTION_H

#include "ActionNode.h"
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <bt_actions/BTAction.h>
namespace BT
{
    class ROSAction : public ActionNode
    {
    public:
        // Constructor
        ROSAction(std::string Name);
        ~ROSAction();

        // The method that is going to be executed by the thread
        void Exec();

        // The method used to interrupt the execution of the node
        bool Halt();

  	//actionlib::SimpleActionClient<bt_actions::BTAction> ac();

	  bt_actions::BTResult node_result;
          bt_actions::BTGoal goal;
    };
}

#endif
