#ifndef TASK_WAIT_FOR_ROI_H
#define TASK_WAIT_FOR_ROI_H

#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_bonirob/BonirobEnv.h"
#include "task_manager_bonirob/TaskWaitForROIConfig.h"

using namespace task_manager_lib;

namespace task_manager_bonirob {
    class TaskWaitForROI : public TaskInstance<TaskWaitForROIConfig,BonirobEnv>
    {
        public:
            TaskWaitForROI(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForROI() {};

            virtual TaskIndicator iterate();

    };
    class TaskFactoryWaitForROI : public TaskDefinition<TaskWaitForROIConfig, BonirobEnv, TaskWaitForROI>
    {
        public:
            TaskFactoryWaitForROI(TaskEnvironmentPtr env) : 
                Parent("WaitForROI","Do nothing until we reach a given destination",true,env) {}
            virtual ~TaskFactoryWaitForROI() {};
    };
};

#endif // TASK_WAIT_FOR_ROI_H
