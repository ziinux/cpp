#ifndef TASK_WAIT4LANDING_H
#define TASK_WAIT4LANDING_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskWaitForLandingRequestConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskWaitForLandingRequest : public TaskInstance<TaskWaitForLandingRequestConfig,SimTasksEnv>
    {
        public:
            TaskWaitForLandingRequest(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitForLandingRequest() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryWaitForLandingRequest : public TaskDefinition<TaskWaitForLandingRequestConfig, SimTasksEnv, TaskWaitForLandingRequest>
    {

        public:
            TaskFactoryWaitForLandingRequest(TaskEnvironmentPtr env) : 
                Parent("WaitForLandingRequest","Wait for a landing request",true,env) {}
            virtual ~TaskFactoryWaitForLandingRequest() {};
    };
};

#endif // TASK_WAIT4LANDING_H
