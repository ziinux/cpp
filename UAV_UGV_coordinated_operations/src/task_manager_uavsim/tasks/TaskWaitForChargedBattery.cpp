#include <math.h>
#include "TaskWaitForChargedBattery.h"
#include "task_manager_uavsim/TaskWaitForChargedBatteryConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;

TaskIndicator TaskWaitForChargedBattery::initialise()
{
    return TaskStatus::TASK_INITIALISED;
}

TaskIndicator TaskWaitForChargedBattery::iterate()
{
    if (env->getBatteryLevel()>chargedThreshold) {
        ROS_INFO("Battery level = %.2f",env->getBatteryLevel());
        return TaskStatus::TASK_COMPLETED;
    }
    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitForChargedBattery::terminate()
{
        return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitForChargedBattery);
