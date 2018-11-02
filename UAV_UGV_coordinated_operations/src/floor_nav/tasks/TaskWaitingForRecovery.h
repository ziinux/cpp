#ifndef TASK_WAIT4RECOVERY_H
#define TASK_WAIT4RECOVERY_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskWaitingForRecoveryConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskWaitingForRecovery : public TaskInstance<TaskWaitingForRecoveryConfig,SimTasksEnv>
    {
        protected:
            ros::Subscriber recoveryReqSub;
            int recovery;
            void recoveryCallBack(const std_msgs::Int32ConstPtr msg) {
                recovery = msg->data;
            }

        public:
            TaskWaitingForRecovery(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitingForRecovery() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryWaitingForRecovery : public TaskDefinition<TaskWaitingForRecoveryConfig, SimTasksEnv, TaskWaitingForRecovery>
    {

        public:
            TaskFactoryWaitingForRecovery(TaskEnvironmentPtr env) : 
                Parent("WaitingForRecovery","Wait for a mission recovery request",true,env) {}
            virtual ~TaskFactoryWaitingForRecovery() {};
    };
};

#endif // TASK_WAIT4RECOVERY_H
