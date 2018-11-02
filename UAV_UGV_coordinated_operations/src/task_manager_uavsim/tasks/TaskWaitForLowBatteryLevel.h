#ifndef TASK_WAIT_FOR_LowBatteryLevel_H
#define TASK_WAIT_FOR_LowBatteryLevel_H

#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskWaitForLowBatteryLevelConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskWaitForLowBatteryLevel : public TaskInstance<TaskWaitForLowBatteryLevelConfig,UAVEnv>
    {
        protected:
            float warningThreshold = 15.0;
        public:
            TaskWaitForLowBatteryLevel(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForLowBatteryLevel() {};

            virtual TaskIndicator initialise();

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();

    };
    class TaskFactoryWaitForLowBatteryLevel : public TaskDefinition<TaskWaitForLowBatteryLevelConfig, UAVEnv, TaskWaitForLowBatteryLevel>
    {
        public:
            TaskFactoryWaitForLowBatteryLevel(TaskEnvironmentPtr env) : 
                Parent("WaitForLowBatteryLevel","wait for landing back order from the ugv",true,env) {}
            virtual ~TaskFactoryWaitForLowBatteryLevel() {};
    };
};

#endif // TASK_WAIT_FOR_LowBatteryLevel_H
