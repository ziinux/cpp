#include <math.h>
#include "TaskWaitForLandingBackOrder.h"
#include "task_manager_uavsim/TaskWaitForLandingBackOrderConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;

TaskIndicator TaskWaitForLandingBackOrder::initialise()
{
    landingBackOrder = -1;
    orderStatusPub = env->getNodeHandle().advertise<std_msgs::Int32>("/landingBackOrderStatus",10);
    landingBackOrderSub = env->getNodeHandle().subscribe("/landingBackOrder",10,&TaskWaitForLandingBackOrder::landingBackOrderCallBack,this);
    return TaskStatus::TASK_INITIALISED;
}

TaskIndicator TaskWaitForLandingBackOrder::iterate()
{
    if (landingBackOrder>0) {
        ROS_INFO("UGV orders a Landing Back !");
        std_msgs::Int32 orderStatus;
        orderStatus.data = 1;
        orderStatusPub.publish(orderStatus);
        return TaskStatus::TASK_COMPLETED;
    }
    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitForLandingBackOrder::terminate()
{
        return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitForLandingBackOrder);
