#include <math.h>
#include "TaskWaitingForTakeOff.h"
#include "floor_nav/TaskWaitingForTakeOffConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskWaitingForTakeOff::initialise() 
{
    ROS_INFO("Waiting for the uav TakeOff");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskWaitingForTakeOff::iterate()
{
    if (env->getTakeOffStatus()==0) 
    {
        // waiting for the uav to start the TakeOff process
        env->publishTakeOffAuthorization(true);
        env->publishPose2D();
    }
    if (env->getTakeOffStatus()==1)
    {
        // TakeOff in progress
        if(env->getSuctionStatus()>0)
        {
            env->setSuction(0);
        }
    }
    if (env->getTakeOffStatus()==2)
    {
        env->publishTakeOffAuthorization(false);
        return TaskStatus::TASK_COMPLETED;
    }

    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitingForTakeOff::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitingForTakeOff);
