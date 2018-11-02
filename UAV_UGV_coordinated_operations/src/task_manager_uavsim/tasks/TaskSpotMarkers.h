#ifndef TASK_SpotMarkers_H
#define TASK_SpotMarkers_H

#include <std_msgs/Int32.h>
#include "task_manager_lib/TaskDefinition.h"
#include "task_manager_uavsim/UAVEnv.h"
#include "task_manager_uavsim/TaskSpotMarkersConfig.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "geometry_msgs/Pose.h"
#include <vector>

using namespace task_manager_lib;

namespace task_manager_uavsim {
    class TaskSpotMarkers : public TaskInstance<TaskSpotMarkersConfig,UAVEnv>
    {
        protected: 
            ros::Publisher ROI_pub;
            ros::Subscriber poseMarkerSub;

            void poseMarker_cb(const ar_track_alvar_msgs::AlvarMarkersConstPtr msg) {
                std::vector<ar_track_alvar_msgs::AlvarMarker> alvarMarkers;
                alvarMarkers = msg->markers;
                if(alvarMarkers.size()>0) env->insertROI(alvarMarkers);
                //ROS_INFO("x = %f, y = %f, theta = %f",pose.position.x,pose.position.y,(pose.orientation.z*2*180.0/3.1415));

            }

        public:
            TaskSpotMarkers(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def,env) {}
            virtual ~TaskSpotMarkers() {};

            virtual TaskIndicator initialise() ;

            virtual TaskIndicator iterate();

            virtual TaskIndicator terminate();
    };
    class TaskFactorySpotMarkers : public TaskDefinition<TaskSpotMarkersConfig, UAVEnv, TaskSpotMarkers>
    {

        public:
            TaskFactorySpotMarkers(TaskEnvironmentPtr env) : 
                Parent("SpotMarkers","Spot the markers and save them",true,env) {}
            virtual ~TaskFactorySpotMarkers() {};
    };
};

#endif // TASK_SpotMarkers_H
