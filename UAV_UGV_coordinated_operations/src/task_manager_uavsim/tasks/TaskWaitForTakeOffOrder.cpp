#include <math.h>
#include "TaskWaitForTakeOffOrder.h"
#include "task_manager_uavsim/TaskWaitForTakeOffOrderConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;

TaskIndicator TaskWaitForTakeOffOrder::initialise()
{
    takeOffOrder = -1;
    orderStatusPub = env->getNodeHandle().advertise<std_msgs::Int32>("/takeOffOrderStatus",10);
    takeOffOrderSub = env->getNodeHandle().subscribe("/takeOffOrder",10,&TaskWaitForTakeOffOrder::takeOffOrderCallBack,this);
    return TaskStatus::TASK_INITIALISED;
}

TaskIndicator TaskWaitForTakeOffOrder::iterate()
{
    if (takeOffOrder>0) {
        ROS_INFO("UGV orders a Take-Off !");
        std_msgs::Int32 orderStatus;
        orderStatus.data = 1;
        
        orderStatusPub.publish(orderStatus);
        orderStatusPub.publish(orderStatus);
        return TaskStatus::TASK_COMPLETED;
    }
    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskWaitForTakeOffOrder::terminate()
{
        std_msgs::Int32 orderStatus;
        orderStatus.data = 1;
        orderStatusPub.publish(orderStatus);
        return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryWaitForTakeOffOrder);
