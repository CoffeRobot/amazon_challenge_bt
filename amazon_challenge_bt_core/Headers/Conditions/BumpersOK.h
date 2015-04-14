#ifndef BUMPERSOK_H
#define BUMPERSOK_H

#include "ConditionNode.h"
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <bt_actions/BTAction.h>
namespace BT
{
    class BumpersOK : public ConditionNode
    {
    public:
        // Constructor
        BumpersOK(std::string Name);
        ~BumpersOK();

        // The method that is going to be executed by the thread
        void Exec();
	  bt_actions::BTResult node_result;
          bt_actions::BTGoal goal;
    };
}

#endif
