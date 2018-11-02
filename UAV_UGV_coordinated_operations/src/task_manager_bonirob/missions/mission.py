#!/usr/bin/python
# ROS specific imports
import roslib; roslib.load_manifest('task_manager_bonirob')
import rospy
from math import *
from task_manager_lib.TaskClient import *

rospy.init_node('task_client')
server_node = rospy.get_param("~server","/bonirob_tasks")
default_period = rospy.get_param("~period",0.2)
tc = TaskClient(server_node,default_period)

wp = [ [1., 9],
    [9., 9.],
    [9., 1.],
    [1., 1.]]

tc.Wait(duration=1.)
tc.GoTo(goal_x=1.0,goal_y=1.0)

for p in wp:
    tc.Wait(duration=0.2)
    tc.GoTo(goal_x=p[0],goal_y=p[1])

tc.Wait(duration=2.)
tc.GoTo(goal_x=5.0,goal_y=5.0)
tc.ReachAngle(target=pi/2)



rospy.loginfo("Mission completed")


