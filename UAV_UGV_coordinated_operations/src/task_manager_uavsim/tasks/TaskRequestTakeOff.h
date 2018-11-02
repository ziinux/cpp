#ifndef TASK_REQUEST_TakeOff_H
#define TASK_REQUEST_TakeOff_H

#include <std_msgs/Int32.h>
#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskRequestTakeOffConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskRequestTakeOff : public TaskInstance<TaskRequestTakeOffConfig,UAVEnv>
    {
        public:
            TaskRequestTakeOff(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskRequestTakeOff() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryRequestTakeOff : public TaskDefinition<TaskRequestTakeOffConfig, UAVEnv, TaskRequestTakeOff>
    {

        public:
            TaskFactoryRequestTakeOff(TaskEnvironmentPtr env) : 
                Parent("RequestTakeOff","Request a Take-Off clearance from the UGV",true,env) {}
            virtual ~TaskFactoryRequestTakeOff() {};
    };
};

#endif // TASK_REQUEST_TakeOff_H
