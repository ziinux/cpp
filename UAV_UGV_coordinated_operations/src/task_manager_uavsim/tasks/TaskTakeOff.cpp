#include <math.h>
#include "TaskTakeOff.h"
#include "task_manager_uavsim/TaskTakeOffConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;


TaskIndicator TaskTakeOff::initialise() 
{
    ROS_INFO("Start Take-Off");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskTakeOff::iterate()
{ 
    if (!env->isMotorON()) 
    {
        env->setMotorON(true);
        return TaskStatus::TASK_RUNNING;
    }
    else
    {
        env->publishTwist(0,0,0,1);       // Go to height = 1
        env->publishTakeOffRequest(false);
        env->publishTakeOffStatus(2);
        return TaskStatus::TASK_COMPLETED;
    }

}

TaskIndicator TaskTakeOff::terminate()
{
    ROS_INFO("Take-Off Successful");
    return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryTakeOff);
