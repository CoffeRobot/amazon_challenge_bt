#ifndef SELECTORSTARNODE_H
#define SELECTORSTARNODE_H

#include <amazon_challenge_bt_core/ControlNode.h>

namespace BT
{
    class SelectorStarNode : public ControlNode
    {
    public:
        // Constructor
        SelectorStarNode(std::string Name);
        ~SelectorStarNode();

        // The method that is going to be executed by the thread
        void Exec();
    };
}

#endif
