#!/usr/bin/python
# ROS specific imports
import roslib; roslib.load_manifest('floor_nav')
import rospy
from math import *
from task_manager_lib.TaskClient import *

rospy.init_node('task_client')
server_node = rospy.get_param("~server","/bubblerob_server")
default_period = rospy.get_param("~period",0.05)
tc = TaskClient(server_node,default_period)
rospy.loginfo("Mission connected to server: " + server_node)

scale=2.0
vel=0.5


try:
#    tc.WaitForAuto()
    while True:
        
        w4takeOffReq = tc.WaitForTakeOffRequest(foreground = False)
        tc.addCondition(ConditionIsCompleted("takeOff Request",tc,w4takeOffReq))
        try:
            print(ConditionIsRunning("takeOff Request",tc,w4takeOffReq))
            tc.GoTo(goal_x=-scale,goal_y=-scale,max_velocity=vel)
            tc.Wait(duration=1.0)
            print(ConditionIsRunning("takeOff Request",tc,w4takeOffReq))
            tc.GoTo(goal_x=-scale,goal_y=scale,max_velocity=vel)
            tc.Wait(duration=1.0)
            print(ConditionIsRunning("takeOff Request",tc,w4takeOffReq))
            tc.GoTo(goal_x=scale,goal_y=scale,max_velocity=vel)
            tc.Wait(duration=1.0)
            tc.GoTo(goal_x=scale,goal_y=-scale,max_velocity=vel)
            tc.Wait(duration=1.0)
            tc.GoTo(goal_x=-scale,goal_y=-scale,max_velocity=vel)
        except TaskConditionException, e:
            print(tc.getVerifiedConditions())
            rospy.loginfo("Mission suspended " + str(e))
            rospy.loginfo("Mission suspended - takeOff requested")
            tc.WaitingForTakeOff()

except TaskException, e:
    rospy.logerr("Exception caught: " + str(e))


if not rospy.core.is_shutdown():
    tc.SetManual()


rospy.loginfo("Mission completed")
