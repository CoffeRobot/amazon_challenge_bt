#include "ConditionNode.h"

using namespace BT;

ConditionNode::ConditionNode(std::string Name) : LeafNode::LeafNode(Name)
{
    Type = Condition;
}

ConditionNode::~ConditionNode() {}

bool ConditionNode::Halt() {}

bool ConditionNode::WriteState(NodeState StateToBeSet)
{
    // Lock acquistion
    boost::lock_guard<boost::mutex> LockGuard(StateMutex);

    State = StateToBeSet;
    return true;
}
