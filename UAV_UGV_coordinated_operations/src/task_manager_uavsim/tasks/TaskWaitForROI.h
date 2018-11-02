#ifndef TASK_WAIT_FOR_ROI_H
#define TASK_WAIT_FOR_ROI_H

#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskWaitForROIConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskWaitForROI : public TaskInstance<TaskWaitForROIConfig,UAVEnv>
    {
        public:
            TaskWaitForROI(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForROI() {};

            virtual TaskIndicator iterate();

    };
    class TaskFactoryWaitForROI : public TaskDefinition<TaskWaitForROIConfig, UAVEnv, TaskWaitForROI>
    {
        public:
            TaskFactoryWaitForROI(TaskEnvironmentPtr env) : 
                Parent("WaitForROI","Do nothing until we reach a given destination",true,env) {}
            virtual ~TaskFactoryWaitForROI() {};
    };
};

#endif // TASK_WAIT_FOR_ROI_H
