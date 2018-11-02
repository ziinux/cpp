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


maxVel=0.5
wp = [ [0., 0], [2., 0.],[0., -2.], [-2., 0.],[0., 2]]
i = 0

try:
    tc.WaitForAuto()
    while True:
        
        w4takeOffReq = tc.WaitForTakeOffRequest(foreground = False)
        w4landingReq = tc.WaitForLandingRequest(foreground = False)
        tc.addCondition(ConditionIsCompleted("takeOff Request",tc,w4takeOffReq))
        tc.addCondition(ConditionIsCompleted("Landing Request",tc,w4landingReq))

        try:
            while True:
                p = wp[i]
                tc.GoTo(goal_x=p[0],goal_y=p[1],max_velocity=maxVel)
                tc.Wait(duration=1.0)
                if (i < 4): 
                    i+=1
                else:
                    i=0
        except TaskConditionException, e:
            if tc.isCompleted(w4takeOffReq):
                rospy.loginfo("Mission suspended - Take-Off Requested !")
                tc.WaitingForTakeOff()
            if tc.isCompleted(w4landingReq):
                rospy.loginfo("Mission suspended - Landing Requested !")
                tc.WaitingForLanding()

except TaskException, e:
    rospy.logerr("Exception caught: " + str(e))


if not rospy.core.is_shutdown():
    tc.SetManual()


rospy.loginfo("Mission completed")
