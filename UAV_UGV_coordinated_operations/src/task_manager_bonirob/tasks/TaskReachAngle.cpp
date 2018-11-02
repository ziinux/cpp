#include <math.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_datatypes.h>
#include "TaskReachAngle.h"
#include "task_manager_bonirob/TaskReachAngleConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_bonirob;

TaskIndicator TaskReachAngle::iterate()
{
    // At every time step, get current orientation
    const geometry_msgs::Quaternion & orientation = env->getPose().pose.orientation;
    double theta = tf::getYaw(orientation);
    // Compute error alpha
    double alpha = remainder(cfg.target-theta,2*M_PI);
    if (fabs(alpha) < cfg.threshold) {
        // If close enough, we're done
		return TaskStatus::TASK_COMPLETED;
    }
    // Compute saturated command rotation speed
    double rot = cfg.k_alpha*alpha;
    if (rot > cfg.max_vrot) rot = cfg.max_vrot;
    if (rot < -cfg.max_vrot) rot = -cfg.max_vrot;
    // Publish pure rotation on the spot
    env->publishVelocity(0.0 , rot);
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskReachAngle::terminate()
{
    env->publishVelocity(0,0);
	return Parent::terminate();
}

DYNAMIC_TASK(TaskFactoryReachAngle);
