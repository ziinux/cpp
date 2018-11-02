#ifndef TASK_WAITING4TakeOff_H
#define TASK_WAITING4TakeOff_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskWaitingForTakeOffConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskWaitingForTakeOff : public TaskInstance<TaskWaitingForTakeOffConfig,SimTasksEnv>
    {
        public:
            TaskWaitingForTakeOff(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskWaitingForTakeOff() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryWaitingForTakeOff : public TaskDefinition<TaskWaitingForTakeOffConfig, SimTasksEnv, TaskWaitingForTakeOff>
    {

        public:
            TaskFactoryWaitingForTakeOff(TaskEnvironmentPtr env) : 
                Parent("WaitingForTakeOff","Waiting until the end of the TakeOff ",true,env) {}
            virtual ~TaskFactoryWaitingForTakeOff() {};
    };
};

#endif // TASK_WAITING4TakeOff_H
