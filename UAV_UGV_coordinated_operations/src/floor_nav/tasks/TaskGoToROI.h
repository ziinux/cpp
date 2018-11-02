#ifndef TASK_GOTOROI_H
#define TASK_GOTOROI_H

#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskGoToROIConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskGoToROI : public TaskInstance<TaskGoToROIConfig,SimTasksEnv>
    {
        protected:
            float goal_x;
            float goal_y;
            int id;
        
        public:
            TaskGoToROI(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskGoToROI() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryGoToROI : public TaskDefinition<TaskGoToROIConfig, SimTasksEnv, TaskGoToROI>
    {

        public:
            TaskFactoryGoToROI(TaskEnvironmentPtr env) : 
                Parent("GoToROI","Reach a desired destination",true,env) {}
            virtual ~TaskFactoryGoToROI() {};
    };
};

#endif // TASK_GOTOROI_H
