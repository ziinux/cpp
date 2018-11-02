#ifndef TASK_ABORT_LANDING_H
#define TASK_ABORT_LANDING_H

#include <std_msgs/Int32.h>
#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskAbortLandingConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskAbortLanding : public TaskInstance<TaskAbortLandingConfig,UAVEnv>
    {
        public:
            TaskAbortLanding(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskAbortLanding() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryAbortLanding : public TaskDefinition<TaskAbortLandingConfig, UAVEnv, TaskAbortLanding>
    {

        public:
            TaskFactoryAbortLanding(TaskEnvironmentPtr env) : 
                Parent("AbortLanding","Inform the ugv that the landing was aborted",true,env) {}
            virtual ~TaskFactoryAbortLanding() {};
    };
};

#endif // TASK_ABORT_LANDING_H
