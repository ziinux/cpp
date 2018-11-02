#include <math.h>
#include "TaskWaitForLandingRequest.h"
#include "floor_nav/TaskWaitForLandingRequestConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskWaitForLandingRequest::initialise() 
{
    ROS_INFO("Waiting for a landing request");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskWaitForLandingRequest::iterate()
{
    if (env->getLandingRequest()) {
        ROS_INFO("landing requested!");
		return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitForLandingRequest::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitForLandingRequest);

