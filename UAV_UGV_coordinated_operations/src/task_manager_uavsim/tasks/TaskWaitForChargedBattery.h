#ifndef TASK_WAIT_FOR_ChargedBattery_H
#define TASK_WAIT_FOR_ChargedBattery_H

#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskWaitForChargedBatteryConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskWaitForChargedBattery : public TaskInstance<TaskWaitForChargedBatteryConfig,UAVEnv>
    {
        protected:
            float chargedThreshold = 90.0;
        public:
            TaskWaitForChargedBattery(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForChargedBattery() {};

            virtual TaskIndicator initialise();

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();

    };
    class TaskFactoryWaitForChargedBattery : public TaskDefinition<TaskWaitForChargedBatteryConfig, UAVEnv, TaskWaitForChargedBattery>
    {
        public:
            TaskFactoryWaitForChargedBattery(TaskEnvironmentPtr env) : 
                Parent("WaitForChargedBattery","wait for landing back order from the ugv",true,env) {}
            virtual ~TaskFactoryWaitForChargedBattery() {};
    };
};

#endif // TASK_WAIT_FOR_ChargedBattery_H
