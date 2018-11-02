#ifndef TASK_WAIT4ORDERTKOFF_H
#define TASK_WAIT4ORDERTKOFF_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskOrderTakeOffConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskOrderTakeOff : public TaskInstance<TaskOrderTakeOffConfig,SimTasksEnv>
    {
        protected:
            ros::Publisher takeOffOrderPub;

        public:
            TaskOrderTakeOff(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskOrderTakeOff() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryOrderTakeOff : public TaskDefinition<TaskOrderTakeOffConfig, SimTasksEnv, TaskOrderTakeOff>
    {

        public:
            TaskFactoryOrderTakeOff(TaskEnvironmentPtr env) : 
                Parent("OrderTakeOff","Order the uav to take-off",true,env) {}
            virtual ~TaskFactoryOrderTakeOff() {};
    };
};

#endif // TASK_WAIT4ORDERTKOFF_H
