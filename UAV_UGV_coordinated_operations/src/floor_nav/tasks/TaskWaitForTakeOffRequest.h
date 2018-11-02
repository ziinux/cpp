#ifndef TASK_WAIT4TAKEOFF_H
#define TASK_WAIT4TAKEOFF_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskWaitForTakeOffRequestConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskWaitForTakeOffRequest : public TaskInstance<TaskWaitForTakeOffRequestConfig,SimTasksEnv>
    {
        public:
            TaskWaitForTakeOffRequest(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForTakeOffRequest() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryWaitForTakeOffRequest : public TaskDefinition<TaskWaitForTakeOffRequestConfig, SimTasksEnv, TaskWaitForTakeOffRequest>
    {

        public:
            TaskFactoryWaitForTakeOffRequest(TaskEnvironmentPtr env) : 
                Parent("WaitForTakeOffRequest","Wait for a take off request",true,env) {}
            virtual ~TaskFactoryWaitForTakeOffRequest() {};
    };
};

#endif // TASK_WAIT4TAKEOFF_H
