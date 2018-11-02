#include <math.h>
#include "TaskRequestTakeOff.h"
#include "task_manager_uavsim/TaskRequestTakeOffConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;


TaskIndicator TaskRequestTakeOff::initialise() 
{
    ROS_INFO("Request TakeOff");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskRequestTakeOff::iterate()
{
    if (!env->getTakeOffAuthorization()) 
    {
        env->publishTakeOffRequest(true);
        env->publishTakeOffStatus(0);
    }
    else
    {
        env->publishTakeOffStatus(1);
        return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskRequestTakeOff::terminate()
{
        ROS_INFO("TakeOff authorized!");
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryRequestTakeOff);
