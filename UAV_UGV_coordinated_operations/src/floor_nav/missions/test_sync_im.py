#!/usr/bin/python
# ROS specific imports
import roslib; roslib.load_manifest('floor_nav')
import rospy
from math import *
from task_manager_lib.TaskClient import *

rospy.init_node('task_client')
server_node = rospy.get_param("~server","/bubblerob_server")
default_period = rospy.get_param("~period",0.05)
ugv = TaskClient(server_node,default_period)
rospy.loginfo("Mission connected to server: " + server_node)


maxVel=0.5
wp = [ [0., 0], [2., 0.],[0., -2.], [-2., 0.],[0., 2]]
i = 0

try:
    ugv.WaitForAuto()
    while True:
        
        w4takeOffReq = ugv.WaitForTakeOffRequest(foreground = False)
        w4landingReq = ugv.WaitForLandingRequest(foreground = False)
        w4interruption = ugv.WaitForInterruption(foreground = False)
        ugv.addCondition(ConditionIsCompleted("takeOff Request",ugv,w4takeOffReq))
        ugv.addCondition(ConditionIsCompleted("Landing Request",ugv,w4landingReq))
        ugv.addCondition(ConditionIsCompleted("Interruption",ugv,w4interruption))

        try:
            while True:
                p = wp[i]
                ugv.GoTo(goal_x=p[0],goal_y=p[1],max_velocity=maxVel)
                ugv.Wait(duration=1.0)
                if (i < 4): 
                    i+=1
                else:
                    i=0
        except TaskConditionException, e:
            if ugv.isCompleted(w4takeOffReq):
                rospy.loginfo("Mission suspended - Take-Off Requested !")
                ugv.WaitingForTakeOff()
            if ugv.isCompleted(w4landingReq):
                rospy.loginfo("Mission suspended - Landing Requested !")
                ugv.WaitingForLanding()
            if ugv.isCompleted(w4interruption):
                rospy.loginfo("Mission suspended - Interruption Requested !")
                ugv.OrderLandingBack()
                ugv.WaitForLandingRequest()
                ugv.WaitingForLanding()
                ugv.WaitingForRecovery()
                ugv.OrderTakeOff()
                ugv.WaitForTakeOffRequest()
                ugv.WaitingForTakeOff()



except TaskException, e:
    rospy.logerr("Exception caught: " + str(e))


if not rospy.core.is_shutdown():
    ugv.SetManual()


rospy.loginfo("Mission completed")
