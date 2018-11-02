#!/usr/bin/python
# ROS specific imports
import roslib; roslib.load_manifest('task_manager_uav')
import rospy
import time
from math import *
from task_manager_lib.TaskClient import *

rospy.init_node('task_client')

# uav task client
server_node_uav = rospy.get_param("~server","/uavsim_tasks")
default_period_uav = rospy.get_param("~period",0.2)
uav = TaskClient(server_node_uav,default_period_uav)
rospy.loginfo("Mission connected to UAV server: " + server_node_uav)

# ugv task client
server_node_ugv = rospy.get_param("~server","/bubblerob_server")
default_period_ugv = rospy.get_param("~period",0.05)
ugv = TaskClient(server_node_ugv,default_period_ugv)
rospy.loginfo("Mission connected to UGV server: " + server_node_ugv)

# press red button to launch the mission
ugv.WaitForAuto()

uav.SetMotor(on=True)
ugv.SetSuction(active=False)

