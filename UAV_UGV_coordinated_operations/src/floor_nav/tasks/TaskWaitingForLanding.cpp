#include <math.h>
#include "TaskWaitingForLanding.h"
#include "floor_nav/TaskWaitingForLandingConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;


TaskIndicator TaskWaitingForLanding::initialise() 
{
    ROS_INFO("Waiting for the uav landing");
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskWaitingForLanding::iterate()
{
    if (env->getLandingStatus()==0) 
    {
        // waiting for the uav to start the landing process
        env->publishLandingAuthorization(true);
        env->publishPose2D();
    }
    if (env->getLandingStatus()==1)
    {
        // landing in progress
        if(env->getSuctionStatus()<=0)
        {
            env->setSuction(1);
        }
    }
    if (env->getLandingStatus()==2)
    {
        env->publishLandingAuthorization(false);
        return TaskStatus::TASK_COMPLETED;
    }

    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitingForLanding::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitingForLanding);
