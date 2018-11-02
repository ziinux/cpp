#ifndef TASK_WAIT_FOR_TakeOffOrder_H
#define TASK_WAIT_FOR_TakeOffOrder_H

#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskWaitForTakeOffOrderConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskWaitForTakeOffOrder : public TaskInstance<TaskWaitForTakeOffOrderConfig,UAVEnv>
    {
        protected:
            ros::Publisher orderStatusPub;
            ros::Subscriber takeOffOrderSub;
            int takeOffOrder;
            void takeOffOrderCallBack(const std_msgs::Int32ConstPtr msg) {
                takeOffOrder = msg->data;
            }

        public:
            TaskWaitForTakeOffOrder(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForTakeOffOrder() {};

            virtual TaskIndicator initialise();

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();

    };
    class TaskFactoryWaitForTakeOffOrder : public TaskDefinition<TaskWaitForTakeOffOrderConfig, UAVEnv, TaskWaitForTakeOffOrder>
    {
        public:
            TaskFactoryWaitForTakeOffOrder(TaskEnvironmentPtr env) : 
                Parent("WaitForTakeOffOrder","wait for landing back order from the ugv",true,env) {}
            virtual ~TaskFactoryWaitForTakeOffOrder() {};
    };
};

#endif // TASK_WAIT_FOR_TakeOffOrder_H
