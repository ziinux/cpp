#include <math.h>
#include "TaskOrderLandingBack.h"
#include "floor_nav/TaskOrderLandingBackConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskOrderLandingBack::initialise() 
{
    ROS_INFO("Order the uav to landing back ");
    landingBackOrderPub = env->getNodeHandle().advertise<std_msgs::Int32>("/landingBackOrder",10);
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskOrderLandingBack::iterate()
{
    std_msgs::Int32 landingBackOrder;
    landingBackOrder.data = 1;
    landingBackOrderPub.publish(landingBackOrder);

    if (env->getLandingBackOrderStatus()>0) {
        ROS_INFO("UAV received the LandingBack Order!");
	return TaskStatus::TASK_COMPLETED;
    }

    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskOrderLandingBack::terminate()
{
        env->setLandingBackOrderStatus(0);
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryOrderLandingBack);

