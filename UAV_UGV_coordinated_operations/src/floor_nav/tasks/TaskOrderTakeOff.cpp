#include <math.h>
#include "TaskOrderTakeOff.h"
#include "floor_nav/TaskOrderTakeOffConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskOrderTakeOff::initialise() 
{
    ROS_INFO("Order the uav to landing back ");
    takeOffOrderPub = env->getNodeHandle().advertise<std_msgs::Int32>("/takeOffOrder",10);
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskOrderTakeOff::iterate()
{
    std_msgs::Int32 takeOffOrder;
    takeOffOrder.data = 1;
    takeOffOrderPub.publish(takeOffOrder);

    if (env->getTakeOffOrderStatus()>0) {
        ROS_INFO("UAV received the TakeOff Order!");
	return TaskStatus::TASK_COMPLETED;
    }

    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskOrderTakeOff::terminate()
{
        env->setTakeOffOrderStatus(0);
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryOrderTakeOff);

