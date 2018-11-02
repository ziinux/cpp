
#include "task_manager_uav/UAVEnv.h"

using namespace task_manager_uav;

UAVEnv::UAVEnv(ros::NodeHandle & n) : task_manager_lib::TaskEnvironment(n)
{
    poseSub = nh.subscribe("/odom",1,&UAVEnv::poseCallback,this);
    velPub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);
}

