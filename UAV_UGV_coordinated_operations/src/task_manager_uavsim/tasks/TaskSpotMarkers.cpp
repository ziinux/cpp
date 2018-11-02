#include <math.h>
#include "TaskSpotMarkers.h"
#include "task_manager_uavsim/TaskSpotMarkersConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;


TaskIndicator TaskSpotMarkers::initialise() 
{
    ROI_pub = env->getNodeHandle().advertise<ar_track_alvar_msgs::AlvarMarkers>("/vrep/drone/targets",1);
    poseMarkerSub = env->getNodeHandle().subscribe("/ar_pose_marker",1,&TaskSpotMarkers::poseMarker_cb,this);
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskSpotMarkers::iterate()
{
/*    if (motor_state < 0) {
        return TaskStatus::TASK_RUNNING;
    }
    if ((motor_state>0) == cfg.on) {
        return TaskStatus::TASK_COMPLETED;
    }*/
    ROI_pub.publish(env->get_ROI_msg());
    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskSpotMarkers::terminate()
{
	return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactorySpotMarkers);
