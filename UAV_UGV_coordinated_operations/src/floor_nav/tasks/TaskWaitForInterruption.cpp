#include <math.h>
#include "TaskWaitForInterruption.h"
#include "floor_nav/TaskWaitForInterruptionConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskWaitForInterruption::initialise() 
{
    ROS_INFO("Waiting for a mission interruption");
    interruption = -1;
    interruptionReqSub = env->getNodeHandle().subscribe("/interruption",1,&TaskWaitForInterruption::interruptionCallBack,this);
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskWaitForInterruption::iterate()
{
    if (interruption>0) {
        ROS_INFO("Interruption requested!");
		return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitForInterruption::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitForInterruption);

