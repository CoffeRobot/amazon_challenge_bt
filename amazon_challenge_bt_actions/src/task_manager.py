#!/usr/bin/env python

# __author__ = 'alessandro'

import json
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int32

# import roslib; roslib.load_manifest('bt_actions')
import actionlib #needed to call receive_update whenever needed
import bt_actions.msg #contains the action message for receive_update

class TaskManager:
  # create messages that are used to publish feedback/result
    _feedback = bt_actions.msg.ObjectsListFeedback()
    _result   = bt_actions.msg.ObjectsListResult()
   
    TASK_COMPLETED = 1
    TASK_CANCELLED = 2
    TASK_POSTPONED = 3
    #rospy.init_node('objectslist')

    
    def __init__(self):
	#Initialize the action (ACTIONLIB)
        rospy.init_node('objectslist')
    	self._action_name = 'objectslist'
  	
    	self._as = actionlib.SimpleActionServer(self._action_name, bt_actions.msg.ObjectsListAction, execute_cb=self.receive_update, auto_start = False)


    	self._as.start()
        self.objects_list = []
        self.data = []
        self.bins = {}
        self.task_list = []
        self.pub = rospy.Publisher('amazon_next_task', String, queue_size = 0)

        #rospy.Subscriber('/amazon_task_update', Int32, self.receive_update)
        self.pub_rate = rospy.Rate(30)

    def add_bin_content(self, bin_id):
        content = self.data['bin_contents']
        self.bins[bin_id] = content[bin_id]

    def init_taks_list(self):
        tasks = self.data['work_order']
        for task in tasks:
            bin = task['bin']
            item = task['item']
            t = [len(self.bins[bin]), item, bin]
            self.task_list.append(t)

        self.task_list.sort(key=lambda tup: tup[0])

        #next_task = self.task_list[0]
        #next_task_msg = '[' + next_task[2] + "," + next_task[1] + ']'
        #print(next_task_msg)

    def receive_update(self,goal):
        rospy.loginfo('Goal Received')
        value = goal.parameter

        if len(self.task_list) < 1:
           self._feedback.status = 1 # a status 1 means that there no more objects in the list
           self._result.status = self._feedback.status
           rospy.loginfo('Task list updated')
	   self._as.set_succeeded(self._result)
           return

        if value == self.TASK_COMPLETED:
            self.task_list.pop(0)
        elif value == self.TASK_CANCELLED:
            self.task_list.pop(0)
        elif value == self.TASK_POSTPONED:
            task = self.task_list.pop(0)
            self.task_list.append(task)
	#set the feedback on the action (ACTIONLIB)
        self._feedback.status = 0 # a status 0 means that there are still objects in the list
        self._result.status = self._feedback.status
        rospy.loginfo('Task list updated')
        self._as.set_succeeded(self._result)
  

    def read_json_list(self, file_path):

        json_data = open(file_path)
        self.data = json.load(json_data)
        json_data.close()

        self.add_bin_content('bin_A')
        self.add_bin_content('bin_B')
        self.add_bin_content('bin_C')
        self.add_bin_content('bin_D')
        self.add_bin_content('bin_E')
        self.add_bin_content('bin_F')
        self.add_bin_content('bin_G')
        self.add_bin_content('bin_H')
        self.add_bin_content('bin_I')
        self.add_bin_content('bin_J')
        self.add_bin_content('bin_K')
        self.add_bin_content('bin_L')

        self.init_taks_list()

    def publish_next_task(self):
        while not rospy.is_shutdown():
            next_task_msg = '[empty,empty]'
            if len(self.task_list) > 0:
                next_task = self.task_list[0]
                next_task_msg = '[' + next_task[2] + "," + next_task[1] + ']'
            self.pub.publish(next_task_msg)
            self.pub_rate.sleep()


task_manager = TaskManager()
task_manager.read_json_list('/home/fevb/amazon_challenge_ws/src/bt_actions/src/example.json')
task_manager.publish_next_task()

