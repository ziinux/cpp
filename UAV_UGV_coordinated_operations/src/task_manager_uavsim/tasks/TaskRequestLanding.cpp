#include <math.h>
#include "TaskRequestLanding.h"
#include "task_manager_uavsim/TaskRequestLandingConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;


TaskIndicator TaskRequestLanding::initialise() 
{
    ROS_INFO("Request landing");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskRequestLanding::iterate()
{
    if (!env->getLandingAuthorization()) 
    {
        env->publishLandingRequest(true);
        env->publishLandingStatus(0);
    }
    else
    {
        env->publishLandingStatus(1);
        return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskRequestLanding::terminate()
{
        ROS_INFO("Landing authorized!");
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryRequestLanding);
