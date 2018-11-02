#include <math.h>
#include "TaskSetMotor.h"
#include "task_manager_uavsim/TaskSetMotorConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;


TaskIndicator TaskSetMotor::initialise() 
{
    motor_state = -1;
    set_motor_pub = env->getNodeHandle().advertise<std_msgs::Int32>("/vrep/drone/motor_on",1);
    motor_state_sub = env->getNodeHandle().subscribe("/vrep/drone/motor_state",1,&TaskSetMotor::motor_cb,this);
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskSetMotor::iterate()
{
    std_msgs::Int32 S;
    S.data = cfg.on?1:0;
    set_motor_pub.publish(S);
    if (motor_state < 0) {
        return TaskStatus::TASK_RUNNING;
    }
    if ((motor_state>0) == cfg.on) {
        return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskSetMotor::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactorySetMotor);
