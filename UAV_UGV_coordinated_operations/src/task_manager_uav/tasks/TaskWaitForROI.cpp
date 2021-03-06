#include <math.h>
#include "TaskWaitForROI.h"
#include "task_manager_uav/TaskWaitForROIConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uav;


TaskIndicator TaskWaitForROI::iterate()
{
    const geometry_msgs::Point & tpose = env->getPose().pose.position;
    double r = hypot(cfg.roi_y-tpose.y,cfg.roi_x-tpose.x);
    if (r < cfg.roi_radius) {
        ROS_INFO("Detected ROI at %.2f %.2f",tpose.x, tpose.y);
		return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

DYNAMIC_TASK(TaskFactoryWaitForROI);
