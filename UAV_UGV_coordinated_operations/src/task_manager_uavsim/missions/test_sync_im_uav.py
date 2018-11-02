#!/usr/bin/python
# ROS specific imports
import roslib; roslib.load_manifest('task_manager_uav')
import rospy
import time
from math import *
from task_manager_lib.TaskClient import *

rospy.init_node('task_client_uav')

# uav task client
server_node_uav = rospy.get_param("~server","/uavsim_tasks")
default_period_uav = rospy.get_param("~period",0.2)
uav = TaskClient(server_node_uav,default_period_uav)
rospy.loginfo("Mission connected to UAV server: " + server_node_uav)


wp = [ [0., 0], [2., -2.], [-2., 2.],[-2., -2.], [2., 2.]]
i=0
try:
    uav.RequestTakeOff()
    uav.Wait(duration=3.0)
    uav.TakeOff()

    while True:

        w4landingBackOrder = uav.WaitForLandingBackOrder(foreground = False)
        w4lowBatteryLevel = uav.WaitForLowBatteryLevel(foreground = False)
        uav.addCondition(ConditionIsCompleted("Landing Back Order",uav,w4landingBackOrder))
        uav.addCondition(ConditionIsCompleted("Low Battery Level",uav,w4lowBatteryLevel))

        try:
            while True:
                p = wp[i]
                uav.GoTo(goal_x=p[0],goal_y=p[1], goal_z=1)
                uav.Wait(duration=1.0)
                if (i < 4):
                    i+=1
                else:
                    i=0
        except TaskConditionException, e:
            if uav.isCompleted(w4landingBackOrder):
                rospy.loginfo("Mission suspended - UGV ordered a Landing Back !")
                uav.RequestLanding()
                uav.Wait(duration=2.0)
                uav.LandingBack()
                uav.WaitForTakeOffOrder()
                uav.RequestTakeOff()
                uav.Wait(duration=2.0)
                uav.TakeOff()  

            if uav.isCompleted(w4lowBatteryLevel):
                rospy.loginfo("Mission suspended - Low battery level ! - starting a Landing Back")
                uav.RequestLanding()
                uav.Wait(duration=2.0)
                uav.LandingBack()
                uav.WaitForChargedBattery()
                uav.RequestTakeOff()
                uav.Wait(duration=2.0)
                uav.TakeOff()

except TaskException, e:
    rospy.logerr("Exception caught: " + str(e))


if not rospy.core.is_shutdown():
    uav.SetManual()

