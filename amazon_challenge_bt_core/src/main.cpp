
#include "ros/ros.h"
#include "std_msgs/UInt8.h"
#include <amazon_challenge_bt_core/BehaviorTree.h>
#include <typeinfo>
#include <math.h>       /* pow */



using namespace BT;

// Global robot variable
//NAO::RobotAction DesiredAction = NAO::None;
//std::mutex DesiredActionMutex;


ActionNode* detect;
ActionNode* grasp;
ActionNode* drop;
ActionNode* posearm;
ActionNode* removeobject;


ConditionNode* detected;
ConditionNode* grasped;
ConditionNode* armposed;

ConditionNode* dropped;
ConditionNode* done;


bool reactiveBT = false;


SequenceStarNode* sequence1;
SelectorStarNode* root;



int GetDepth(TreeNode* tree )
{
    ControlNode* d = dynamic_cast<ControlNode*> (tree);
    if (d != NULL)
    {//if a control flow node
        int M = d->GetChildrenNumber();
        std::vector<TreeNode*> children = d->GetChildren();

        int depMax = 0;
        int dep = 0;
        for (int i = 0; i < M; i++)
        {
           dep = GetDepth(children[i]);
           if (dep > depMax)
           {
               depMax = dep;
           }

        }
      return 1 + depMax;
    }
    else
    {
    return 0;
    }

}

void updateTree(TreeNode* tree, GLfloat x_pos, GLfloat y_pos, GLfloat x_offset, GLfloat y_offset )
{
    ControlNode* d = dynamic_cast<ControlNode*> (tree);
    if (d == NULL)
    {//if it is a leaf node, draw it

        draw_node((GLfloat) x_pos, (GLfloat) y_pos, tree->GetType(), tree->Name.c_str(), tree->ReadColorState());
    }
    else
    {//if it is a control flow node, draw it and its children
        draw_node((GLfloat) x_pos, (GLfloat) y_pos, tree->GetType(), tree->Name.c_str(), tree->ReadColorState());
        std::vector<TreeNode*> children = d->GetChildren();
        int M = d->GetChildrenNumber();
        for (int i = M-1; i >= 0; i--)
        {
            updateTree(children[i], x_pos - x_offset * (M-1) + 2*x_offset*(i) , y_pos - y_offset , x_offset/2  ,y_offset );
            draw_edge(x_pos, y_pos, 0.02, x_pos - x_offset * (M-1) + 2*x_offset*(i) , y_pos - y_offset, 0.02);
        }
    }
}


void display()
{


    // clear the draw buffer .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything
    updateTree(root, 0.0 , 0.4, pow(0.6,GetDepth(root)) , 0.1 );
    glutSwapBuffers();
    glutPostRedisplay();

}







void drawTree()
{
    //***************************BT VISUALIZATION****************************
    int argc = 1;
    char *argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);      // Initialize GLUT
    glutInitWindowSize(1024,1024);

    glutCreateWindow("Behavior Tree");  // Create a window
    glutReshapeFunc(resize);
    glClearColor( 1, 1, 1, 0.5);
    glutDisplayFunc(display);   // Register display callback


    glutKeyboardFunc(keyboard); // Register keyboard callback
    glutMainLoop();             // Enter main event loop

    //***************************ENDOF BT VISUALIZATION ****************************

}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "Main");


    detect = new ROSAction("detector_node");
    grasp = new ROSAction("grasp_object");
    drop = new ROSAction("drop_object");
    posearm = new ROSAction("arm_position_server");
    removeobject = new ROSAction("remove_object");


    detected = new ROSCondition("object_detected");
    grasped = new ROSCondition("object_grasped");
    armposed = new ROSCondition("arm_posed");
    dropped = new ROSCondition("object_dropped");
    done = new ROSCondition("list_done");


     sequence1 = new SequenceStarNode("seq1");
    root = new SelectorStarNode("root");






    std::cout << "Start Drawing!" << std::endl;

    boost::thread t(&drawTree);

    std::cout << "Drawing Done!" << std::endl;



    // ros::NodeHandle Handle;

    // ros::Subscriber Subscriber = Handle.subscribe<std_msgs::UInt8>("Inputs", 10, chatterCallback);

    // ros::spin();
    int TickPeriod_milliseconds = 1000;



    try
    {



        sequence1->AddChild(posearm);
        sequence1->AddChild(grasp);
        sequence1->AddChild(drop);
        sequence1->AddChild(removeobject);

        root->AddChild(done);
        root->AddChild(sequence1);



        root->ResetColorState();

        while(ros::ok())
        {


            std::cout << "Ticking the root node !" << std::endl << std::endl;

            // Ticking the root node
            root->Semaphore.Signal();
            // Printing its state
            //std::cout << sequence1->Name << " returned " << sequence1->GetNodeState() << "!" << std::endl << std::endl;
            root->GetNodeState();

            if(root->ReadState() != Running  )
            {
                root->ResetColorState();

            }
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






/*
    if (reactiveBT)
    {
        SequenceNode* sequence1 = new SequenceNode("seq1");
        SequenceNode* sequence2 = new SequenceNode("seq2");
        root = new SelectorNode("root");
        SelectorNode* selector1 = new SelectorNode("sel1");
        SelectorNode* selector2 = new SelectorNode("sel2");
        SelectorNode* selector3 = new SelectorNode("sel3");

        ParallelNode* parallel1 = new ParallelNode("par1");
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

    }else
     {

        SequenceStarNode* sequence1 = new SequenceStarNode("seq1");
       // SequenceStarNode* sequence2 = new SequenceStarNode("seq2");
        //root = new SelectorStarNode("root");
        //SelectorStarNode* selector1 = new SelectorStarNode("sel1");
        root = new SelectorStarNode("root");


        sequence1->AddChild(posearm);
        sequence1->AddChild(grasp);
        sequence1->AddChild(drop);

        sequence1->AddChild(remove);

        root->AddChild(done);
        root->AddChild(sequence1);

    }




*/
