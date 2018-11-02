#ifndef TASK_REQUEST_LANDING_H
#define TASK_REQUEST_LANDING_H

#include <std_msgs/Int32.h>
#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskRequestLandingConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskRequestLanding : public TaskInstance<TaskRequestLandingConfig,UAVEnv>
    {
        public:
            TaskRequestLanding(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskRequestLanding() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryRequestLanding : public TaskDefinition<TaskRequestLandingConfig, UAVEnv, TaskRequestLanding>
    {

        public:
            TaskFactoryRequestLanding(TaskEnvironmentPtr env) : 
                Parent("RequestLanding","Request a landing clearance from the UGV",true,env) {}
            virtual ~TaskFactoryRequestLanding() {};
    };
};

#endif // TASK_REQUEST_LANDING_H
