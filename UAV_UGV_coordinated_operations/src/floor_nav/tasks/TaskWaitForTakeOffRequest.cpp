#include <math.h>
#include "TaskWaitForTakeOffRequest.h"
#include "floor_nav/TaskWaitForTakeOffRequestConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskWaitForTakeOffRequest::initialise() 
{
    ROS_INFO("Waiting for a take off request");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskWaitForTakeOffRequest::iterate()
{
    if (env->getTakeOffRequest()) {
        ROS_INFO("take off requested!");
		return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitForTakeOffRequest::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitForTakeOffRequest);

