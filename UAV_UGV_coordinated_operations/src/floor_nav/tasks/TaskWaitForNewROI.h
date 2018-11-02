#ifndef TASK_WAITNewROI_H
#define TASK_WAITNewROI_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskWaitForNewROIConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskWaitForNewROI : public TaskInstance<TaskWaitForNewROIConfig,SimTasksEnv>
    {
        public:
            TaskWaitForNewROI(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForNewROI() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryWaitForNewROI : public TaskDefinition<TaskWaitForNewROIConfig, SimTasksEnv, TaskWaitForNewROI>
    {

        public:
            TaskFactoryWaitForNewROI(TaskEnvironmentPtr env) : 
                Parent("WaitForNewROI","Wait for a new ROI",true,env) {}
            virtual ~TaskFactoryWaitForNewROI() {};
    };
};

#endif // TASK_WAITNewROI_H
