#ifndef TASK_WAIT4ORDERLNDBCK_H
#define TASK_WAIT4ORDERLNDBCK_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskOrderLandingBackConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskOrderLandingBack : public TaskInstance<TaskOrderLandingBackConfig,SimTasksEnv>
    {
        protected:
            ros::Publisher landingBackOrderPub;

        public:
            TaskOrderLandingBack(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskOrderLandingBack() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryOrderLandingBack : public TaskDefinition<TaskOrderLandingBackConfig, SimTasksEnv, TaskOrderLandingBack>
    {

        public:
            TaskFactoryOrderLandingBack(TaskEnvironmentPtr env) : 
                Parent("OrderLandingBack","Order the uav to interrupt its mission and landing back",true,env) {}
            virtual ~TaskFactoryOrderLandingBack() {};
    };
};

#endif // TASK_WAIT4ORDERLNDBCK_H
