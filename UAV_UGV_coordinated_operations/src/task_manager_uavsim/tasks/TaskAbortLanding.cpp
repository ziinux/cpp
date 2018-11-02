#include <math.h>
#include "TaskAbortLanding.h"
#include "task_manager_uavsim/TaskAbortLandingConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;


TaskIndicator TaskAbortLanding::initialise() 
{
    ROS_INFO("Request landing");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskAbortLanding::iterate()
{
    env->publishLandingRequest(false);
    env->publishLandingStatus(2);
    return TaskStatus::TASK_COMPLETED;
}

TaskIndicator TaskAbortLanding::terminate()
{
        ROS_INFO("Landing authorized!");
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryAbortLanding);
