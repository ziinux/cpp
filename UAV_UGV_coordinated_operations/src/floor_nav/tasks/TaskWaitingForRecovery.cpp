#include <math.h>
#include "TaskWaitingForRecovery.h"
#include "floor_nav/TaskWaitingForRecoveryConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskWaitingForRecovery::initialise() 
{
    ROS_INFO("Waiting for a mission recovery");
    recovery = -1;
    recoveryReqSub = env->getNodeHandle().subscribe("/recovery",1,&TaskWaitingForRecovery::recoveryCallBack,this);
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskWaitingForRecovery::iterate()
{
    if (recovery>0) {
        ROS_INFO("Recovery requested!");
		return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitingForRecovery::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitingForRecovery);

