#ifndef TASK_WAIT_FOR_LandingBackOrder_H
#define TASK_WAIT_FOR_LandingBackOrder_H

#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskWaitForLandingBackOrderConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskWaitForLandingBackOrder : public TaskInstance<TaskWaitForLandingBackOrderConfig,UAVEnv>
    {
        protected:
            ros::Publisher orderStatusPub;
            ros::Subscriber landingBackOrderSub;
            int landingBackOrder;
            void landingBackOrderCallBack(const std_msgs::Int32ConstPtr msg) {
                landingBackOrder = msg->data;
            }

        public:
            TaskWaitForLandingBackOrder(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForLandingBackOrder() {};

            virtual TaskIndicator initialise();

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();

    };
    class TaskFactoryWaitForLandingBackOrder : public TaskDefinition<TaskWaitForLandingBackOrderConfig, UAVEnv, TaskWaitForLandingBackOrder>
    {
        public:
            TaskFactoryWaitForLandingBackOrder(TaskEnvironmentPtr env) : 
                Parent("WaitForLandingBackOrder","wait for landing back order from the ugv",true,env) {}
            virtual ~TaskFactoryWaitForLandingBackOrder() {};
    };
};

#endif // TASK_WAIT_FOR_LandingBackOrder_H
