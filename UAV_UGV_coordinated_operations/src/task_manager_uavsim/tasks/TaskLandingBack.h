#ifndef TASK_LANDING_BACK_H
#define TASK_LANDING_BACK_H

#include <std_msgs/Int32.h>
#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskLandingBackConfig.h"

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskLandingBack : public TaskInstance<TaskLandingBackConfig,UAVEnv>
    {
        protected:
            geometry_msgs::Pose2D ugvPose;

        public:
            TaskLandingBack(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskLandingBack() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryLandingBack : public TaskDefinition<TaskLandingBackConfig, UAVEnv, TaskLandingBack>
    {

        public:
            TaskFactoryLandingBack(TaskEnvironmentPtr env) : 
                Parent("LandingBack","UAV Landing Back",true,env) {}
            virtual ~TaskFactoryLandingBack() {};
    };
};

#endif // TASK_LANDING_BACK_H
