#ifndef TASK_REACH_ANGLE_H
#define TASK_REACH_ANGLE_H

#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_bonirob/BonirobEnv.h"
#include "task_manager_bonirob/TaskReachAngleConfig.h"
using namespace task_manager_lib;

namespace task_manager_bonirob {
    class TaskReachAngle : public TaskInstance<TaskReachAngleConfig,BonirobEnv>
    {
        public:
            TaskReachAngle(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskReachAngle() {};

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactoryReachAngle : public TaskDefinition<TaskReachAngleConfig, BonirobEnv, TaskReachAngle>
    {
        public:
            TaskFactoryReachAngle(TaskEnvironmentPtr env) : 
                Parent("ReachAngle","Reach a desired angular set-point",true,env) {}
            virtual ~TaskFactoryReachAngle() {};
    };
};

#endif // TASK_REACH_ANGLE_H
