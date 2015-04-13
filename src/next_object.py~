#! /usr/bin/env python

import roslib; roslib.load_manifest('bt_actions')
import rospy

import actionlib

import bt_actions.msg



class BTAction(object):
  # create messages that are used to publish feedback/result
  _feedback = bt_actions.msg.BTFeedback()
  _result   = bt_actions.msg.BTResult()

  def __init__(self, name):
    self._action_name = name
    self._as = actionlib.SimpleActionServer(self._action_name, bt_actions.msg.BTAction, execute_cb=self.execute_cb, auto_start = False)
    self._as.start()
    
  def execute_cb(self, goal):
    # helper variables
    r = rospy.Rate(1)
    success = True
    

    
    # publish info to the console for the user
    rospy.loginfo('Starting Action')
    
    # start executing the action
    for i in xrange(1, 2):
      # check that preempt has not been requested by the client
      if self._as.is_preempt_requested():
        rospy.loginfo('Action Halted')
        self._as.set_preempted()
        success = False
        break

      rospy.loginfo('Executing Action')

      client = actionlib.SimpleActionClient('objectslist', bt_actions.msg.ObjectsListAction)

        # Waits until the action server has started up and started
        # listening for goals.
      rospy.loginfo('Start Waiting')
      client.wait_for_server()

        # Creates a goal to send to the action server.
      goal = bt_actions.msg.ObjectsListGoal(parameter=1)

            # Sends the goal to the action server.
      client.send_goal(goal)
      rospy.loginfo('Goal Sent')
            # Waits for the server to finish performing the action.
      client.wait_for_result()
      self.set_status('SUCCESS')
      # this step is not necessary, the sequence is computed at 1 Hz for demonstration purposes
      r.sleep()
      



    

  def set_status(self,status):
      if status == 'SUCCESS':
        self._feedback.status = 1
        self._result.status = self._feedback.status
        rospy.loginfo('Action %s: Succeeded' % self._action_name)
        self._as.set_succeeded(self._result)
      elif status == 'FAILURE':
        self._feedback.status = 2
        self._result.status = self._feedback.status
        rospy.loginfo('Action %s: Failed' % self._action_name)
        self._as.set_succeeded(self._result)
      else:
        rospy.logerr('Action %s: has a wrong return status' % self._action_name)



if __name__ == '__main__':
  rospy.init_node('action')
  BTAction(rospy.get_name())
  rospy.spin()
