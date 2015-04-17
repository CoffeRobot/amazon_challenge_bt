#include "ros/ros.h"
#include "std_msgs/UInt8.h"
#include <amazon_challenge_bt_core/BehaviorTree.h>



using namespace BT;

// Global robot variable
//NAO::RobotAction DesiredAction = NAO::None;
//std::mutex DesiredActionMutex;

int main(int argc, char **argv)
{

    ros::init(argc, argv, "Main");
    // ros::NodeHandle Handle;

    // ros::Subscriber Subscriber = Handle.subscribe<std_msgs::UInt8>("Inputs", 10, chatterCallback);

    // ros::spin();
    int TickPeriod_milliseconds = 100;

    try
    {
        SequenceNode* sequence1 = new SequenceNode("seq1");
        SequenceNode* sequence2 = new SequenceNode("seq2");
        SelectorNode* root = new SelectorNode("root");
        SelectorNode* selector1 = new SelectorNode("sel1");
        SelectorNode* selector2 = new SelectorNode("sel2");
        SelectorNode* selector3 = new SelectorNode("sel3");

        ParallelNode* parallel1 = new ParallelNode("par1");


        //ActionNode* actTest = new ActionTestNode("move");
//ConditionNode* conbump = new BumpersOK("cond");

//sequence1->AddChild(conbump);
//sequence1->AddChild(actTest);



    ActionNode* detect = new ROSAction("detector_node");
    ActionNode* grasp = new ROSAction("grasp_object");
    ActionNode* drop = new ROSAction("drop_object");
    ActionNode* posearm = new ROSAction("arm_position_server");
    ActionNode* remove = new ROSAction("remove_object");


    ConditionNode* detected = new ROSCondition("object_detected");
    ConditionNode* grasped = new ROSCondition("object_grasped");
    ConditionNode* armposed = new ROSCondition("arm_posed");

    ConditionNode* dropped = new ROSCondition("object_dropped");
    ConditionNode* done = new ROSCondition("list_done");


/*

    selector1->AddChild(detected);
    selector1->AddChild(detect);

    selector2->AddChild(grasped);
    selector2->AddChild(grasp);

    sequence1->AddChild(selector1);
    sequence1->AddChild(selector2);
    sequence1->AddChild(drop);
    sequence1->AddChild(remove);

    root->AddChild(done);
    root->AddChild(sequence1);
*/

   // parallel1->AddChild(detect);
    //parallel1->AddChild(grasp);

    //parallel1->SetThreashold(2);
    selector1->AddChild(armposed);
    selector1->AddChild(posearm);
    selector2->AddChild(grasped);
    selector2->AddChild(grasp);

    selector3->AddChild(dropped);
    selector3->AddChild(drop);

    sequence1->AddChild(selector1);
    sequence1->AddChild(selector2);
    sequence1->AddChild(selector3);

    sequence1->AddChild(remove);

    root->AddChild(done);
    root->AddChild(sequence1);
    //root->AddChild(grasp);



        while(ros::ok())
        {
 			std::cout << "Ticking the root node !" << std::endl << std::endl;

            // Ticking the root node
            root->Semaphore.Signal();
            // Printing its state
            //std::cout << sequence1->Name << " returned " << sequence1->GetNodeState() << "!" << std::endl << std::endl;
            root->GetNodeState();
            // Simulating the tick period
            boost::this_thread::sleep(boost::posix_time::milliseconds(TickPeriod_milliseconds));
        
        }

       // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    }
    catch (BehaviorTreeException& Exception)
    {
        std::cout << Exception.what() << std::endl;
    }

    return 0;
}

