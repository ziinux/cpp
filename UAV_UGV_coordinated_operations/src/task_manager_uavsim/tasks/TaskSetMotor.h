#ifndef TASK_SET_MOTOR_H
#define TASK_SET_MOTOR_H

#include <std_msgs/Int32.h>
#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskSetMotorConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskSetMotor : public TaskInstance<TaskSetMotorConfig,UAVEnv>
    {
        protected: 
            ros::Publisher set_motor_pub;
            ros::Subscriber motor_state_sub;

            int motor_state;
            void motor_cb(const std_msgs::Int32ConstPtr msg) {
                motor_state = msg->data;
            }

        public:
            TaskSetMotor(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskSetMotor() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactorySetMotor : public TaskDefinition<TaskSetMotorConfig, UAVEnv, TaskSetMotor>
    {

        public:
            TaskFactorySetMotor(TaskEnvironmentPtr env) : 
                Parent("SetMotor","Control the state of UAV propellers",true,env) {}
            virtual ~TaskFactorySetMotor() {};
    };
};

#endif // TASK_SET_MOTOR_H
