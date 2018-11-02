#ifndef TASK_WAITING4LANDING_H
#define TASK_WAITING4LANDING_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskWaitingForLandingConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskWaitingForLanding : public TaskInstance<TaskWaitingForLandingConfig,SimTasksEnv>
    {
        public:
            TaskWaitingForLanding(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitingForLanding() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryWaitingForLanding : public TaskDefinition<TaskWaitingForLandingConfig, SimTasksEnv, TaskWaitingForLanding>
    {

        public:
            TaskFactoryWaitingForLanding(TaskEnvironmentPtr env) : 
                Parent("WaitingForLanding","Wait for a landing request",true,env) {}
            virtual ~TaskFactoryWaitingForLanding() {};
    };
};

#endif // TASK_WAITING4LANDING_H
