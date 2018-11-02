#include <math.h>
#include <unistd.h>
#include <tf/transform_datatypes.h>
#include "TaskLandingBack.h"
#include "task_manager_uavsim/TaskLandingBackConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace task_manager_uavsim;


TaskIndicator TaskLandingBack::initialise() 
{
    ugvPose = env->getUGVPose();
    ROS_INFO("Start Landing back to X = %.2f Y = %.2f Theta = %.2f",ugvPose.x,ugvPose.y,ugvPose.theta*180/3.1415);
    return TaskStatus::TASK_INITIALISED;
}


TaskIndicator TaskLandingBack::iterate()
{

    geometry_msgs::Pose pose = env->getPose();
    double theta = tf::getYaw(pose.orientation);
    double r = hypot(ugvPose.y-pose.position.y,ugvPose.x-pose.position.x);
    if (r < cfg.dist_threshold) {
        // If close enough, we're done
        if (env->isMotorON())
        {
            double height = 0.35;
            env->publishTwist(0,0,0,height);
            //ROS_INFO("Z = %.2f",pose.position.z);
            if(pose.position.z <= height) env->setMotorON(false);
            return TaskStatus::TASK_RUNNING;
        }
        env->publishLandingRequest(false);
        env->publishLandingStatus(2);
        return TaskStatus::TASK_COMPLETED;
    }
    // Compute bearing error to the target
    double alpha = remainder(atan2((ugvPose.y-pose.position.y),ugvPose.x-pose.position.x)-theta,2*M_PI);
    double height = 1;
    if (fabs(alpha) > M_PI/6) {
        // If bearing error is too high, output a pure rotation command
        double rot = ((alpha>0)?+1:-1)*M_PI/6;
        env->publishTwist(0,0,rot,height);
    } else {
        // Otherwise, add a saturated linear velocity
        double vel = cfg.k_v * r;
        double rot = cfg.k_alpha*alpha;
        if (vel > cfg.max_velocity) vel = cfg.max_velocity;
        env->publishTwist(vel, 0, rot,height);
    }
        return TaskStatus::TASK_RUNNING;

}

TaskIndicator TaskLandingBack::terminate()
{
    ROS_INFO("Landing Successful");
    return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryLandingBack);
