#include <math.h>
#include <tf/transform_datatypes.h>
#include "TaskGoTo.h"
#include "task_manager_bonirob/TaskGoToConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_bonirob;


TaskIndicator TaskGoTo::initialise()  {
    ROS_INFO("TaskGoTo: Going to (%.2f,%.2f)",cfg.goal_x,cfg.goal_y);
    return TaskStatus::TASK_INITIALISED;
}
            

TaskIndicator TaskGoTo::iterate()
{
    // At every time step, get current pose
    const geometry_msgs::Pose & pose = env->getPose().pose;
    double theta = tf::getYaw(pose.orientation);
    double r = hypot(cfg.goal_y-pose.position.y,cfg.goal_x-pose.position.x);
    if (r < cfg.dist_threshold) {
        // If close enough, we're done
		return TaskStatus::TASK_COMPLETED;
    }
    // Compute bearing error to the target
    double alpha = remainder(atan2((cfg.goal_y-pose.position.y),cfg.goal_x-pose.position.x)-theta,2*M_PI);
    if (fabs(alpha) > M_PI/6) {
        // If bearing error is too high, output a pure rotation command
        double rot = ((alpha>0)?+1:-1)*M_PI/6;
        env->publishVelocity(0,rot);
    } else {
        // Otherwise, add a saturated linear velocity
        double vel = cfg.k_v * r;
        double rot = cfg.k_alpha*alpha;
        if (vel > cfg.max_velocity) vel = cfg.max_velocity;
        env->publishVelocity(vel, rot);
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskGoTo::terminate()
{
    env->publishVelocity(0,0);
	return Parent::terminate();
}

DYNAMIC_TASK(TaskFactoryGoTo);
