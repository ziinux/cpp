#ifndef TASK_SET_SUCTION_H
#define TASK_SET_SUCTION_H

#include <std_msgs/Int32.h>
#include "task_manager_lib/TaskDefinition.h"
#include "floor_nav/SimTasksEnv.h"
#include "floor_nav/TaskSetSuctionConfig.h"

using namespace task_manager_lib;

namespace floor_nav {
    class TaskSetSuction : public TaskInstance<TaskSetSuctionConfig,SimTasksEnv>
    {
        protected: 
            ros::Publisher set_suction_pub;
            ros::Subscriber suction_state_sub;

            int suction_state;
            void suction_cb(const std_msgs::Int32ConstPtr msg) {
                suction_state = msg->data;
            }

        public:
            TaskSetSuction(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskSetSuction() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactorySetSuction : public TaskDefinition<TaskSetSuctionConfig, SimTasksEnv, TaskSetSuction>
    {

        public:
            TaskFactorySetSuction(TaskEnvironmentPtr env) : 
                Parent("SetSuction","Control the state of the suction cup",true,env) {}
            virtual ~TaskFactorySetSuction() {};
    };
};

#endif // TASK_SET_SUCTION_H
