#include <math.h>
#include "TaskGoToROI.h"
#include "floor_nav/TaskGoToROIConfig.h"
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;

// #define DEBUG_GOTOROI
#ifdef DEBUG_GOTOROI
#warning Debugging task GOTOROI
#endif


TaskIndicator TaskGoToROI::initialise()
{
    std::map<int, geometry_msgs::PoseStamped>::iterator it;
    std::map <int,geometry_msgs::PoseStamped> ROI = env->getROI();
    for(it = ROI.begin();it != ROI.end(); ++it)
    {
        if(env->isVisited(it->first))
        {
            if(it==ROI.end()) 
            {
                ROS_INFO("No new ROI found");
                return TaskStatus::TASK_TERMINATED;
            }
            continue;
        }
        else
        {
            goal_x = it->second.pose.position.x;
            goal_y = it->second.pose.position.y;
            id = it->first;
            ROS_INFO("Going to %.2f %.2f, id = %d",goal_x,goal_y,id);
            return TaskStatus::TASK_INITIALISED;
        }
    }
}


TaskIndicator TaskGoToROI::iterate()
{
    const geometry_msgs::Pose2D & tpose = env->getPose2D();
    double r = hypot(goal_y-tpose.y,goal_x-tpose.x);
    if (r < cfg.dist_threshold) {
		return TaskStatus::TASK_COMPLETED;
    }
    double alpha = remainder(atan2((goal_y-tpose.y),goal_x-tpose.x)-tpose.theta,2*M_PI);
#ifdef DEBUG_GOTOROI
    printf("c %.1f %.1f %.1f g %.1f %.1f r %.3f alpha %.1f\n",
            tpose.x, tpose.y, tpose.theta*180./M_PI,
            goal_x,goal_y,r,alpha*180./M_PI);
#endif
    if (fabs(alpha) > M_PI/9) {
        double rot = ((alpha>0)?+1:-1)*cfg.max_angular_velocity;
#ifdef DEBUG_GOTOROI
        printf("Cmd v %.2f r %.2f\n",0.,rot);
#endif
        env->publishVelocity(0,rot);
    } else {
        double vel = cfg.k_v * r;
        double rot = std::max(std::min(cfg.k_alpha*alpha,cfg.max_angular_velocity),-cfg.max_angular_velocity);
        if (vel > cfg.max_velocity) vel = cfg.max_velocity;
#ifdef DEBUG_GOTOROI
        printf("Cmd v %.2f r %.2f\n",vel,rot);
#endif
        env->publishVelocity(vel, rot);
    }
	return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskGoToROI::terminate()
{
    env->publishVelocity(0,0);
    env->setVisited(id);
    return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryGoToROI);
