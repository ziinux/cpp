#ifndef TASK_WAIT4INTERRUPTION_H
#define TASK_WAIT4INTERRUPTION_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskWaitForInterruptionConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskWaitForInterruption : public TaskInstance<TaskWaitForInterruptionConfig,SimTasksEnv>
    {
        protected:
            ros::Subscriber interruptionReqSub;
            int interruption;
            void interruptionCallBack(const std_msgs::Int32ConstPtr msg) {
                interruption = msg->data;
            }

        public:
            TaskWaitForInterruption(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForInterruption() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryWaitForInterruption : public TaskDefinition<TaskWaitForInterruptionConfig, SimTasksEnv, TaskWaitForInterruption>
    {

        public:
            TaskFactoryWaitForInterruption(TaskEnvironmentPtr env) : 
                Parent("WaitForInterruption","Wait for a mission interruption request",true,env) {}
            virtual ~TaskFactoryWaitForInterruption() {};
    };
};

#endif // TASK_WAIT4INTERRUPTION_H
