#include <math.h>
#include "TaskWaitForLowBatteryLevel.h"
#include "task_manager_uavsim/TaskWaitForLowBatteryLevelConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;

TaskIndicator TaskWaitForLowBatteryLevel::initialise()
{
    return TaskStatus::TASK_INITIALISED;
}

TaskIndicator TaskWaitForLowBatteryLevel::iterate()
{
    if (env->getBatteryLevel()<warningThreshold) {
        ROS_INFO("Battery level is low !!");
        return TaskStatus::TASK_COMPLETED;
    }
    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitForLowBatteryLevel::terminate()
{
        return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitForLowBatteryLevel);
