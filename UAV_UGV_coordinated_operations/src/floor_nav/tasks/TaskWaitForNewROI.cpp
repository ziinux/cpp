#include <math.h>
#include "TaskWaitForNewROI.h"
#include "floor_nav/TaskWaitForNewROIConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskWaitForNewROI::initialise() 
{
    ROS_INFO("Waiting for newROI");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskWaitForNewROI::iterate()
{
    if (env->isThereNewROI()) {
        ROS_INFO("NewROI Found!");
        return TaskStatus::TASK_COMPLETED;
    }
    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitForNewROI::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitForNewROI);
