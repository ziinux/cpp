#include <math.h>
#include "TaskSetSuction.h"
#include "floor_nav/TaskSetSuctionConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;

// #define DEBUG_GOTO
#ifdef DEBUG_GOTO
#warning Debugging task GOTO
#endif


TaskIndicator TaskSetSuction::initialise() 
{
    suction_state = -1;
    set_suction_pub = env->getNodeHandle().advertise<std_msgs::Int32>("/vrep/bubblerob/suctionCommand",1);
    suction_state_sub = env->getNodeHandle().subscribe("/vrep/bubblerob/suctionState",1,&TaskSetSuction::suction_cb,this);
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskSetSuction::iterate()
{
    std_msgs::Int32 S;
    S.data = cfg.active?1:0;
    set_suction_pub.publish(S);
    if (suction_state < 0) {
        return TaskStatus::TASK_RUNNING;
    }
    if ((suction_state>0) == cfg.active) {
        return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskSetSuction::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactorySetSuction);
