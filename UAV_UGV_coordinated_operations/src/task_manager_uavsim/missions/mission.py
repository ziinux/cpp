#!/usr/bin/python
# ROS specific imports
import roslib; roslib.load_manifest('task_manager_uav')
import rospy
from math import *
from task_manager_lib.TaskClient import *

rospy.init_node('task_client')
server_node = rospy.get_param("~server","/uavsim_tasks")
default_period = rospy.get_param("~period",0.2)
tc = TaskClient(server_node,default_period)

wp = [ [0., 0., 0.5], [0., 2., 0.5], [2., 0., 0.5],
    [0., -2., 0.5], [-2., 0., 0.5],[0., 0., 0.5]] 


tc.SetMotor(on=True)
for p in wp:
    tc.Wait(duration=0.2)
    tc.GoTo(goal_x=p[0],goal_y=p[1], goal_z=p[2])

tc.ReachAngle(target=pi/2)
tc.SetMotor(on=False)



rospy.loginfo("Mission completed")


