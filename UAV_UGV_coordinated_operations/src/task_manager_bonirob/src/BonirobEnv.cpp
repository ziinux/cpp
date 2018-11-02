
#include "task_manager_bonirob/BonirobEnv.h"

using namespace task_manager_bonirob;

BonirobEnv::BonirobEnv(ros::NodeHandle & n) : task_manager_lib::TaskEnvironment(n)
{
    poseSub = nh.subscribe("/odom",1,&BonirobEnv::poseCallback,this);
    velPub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);
}

