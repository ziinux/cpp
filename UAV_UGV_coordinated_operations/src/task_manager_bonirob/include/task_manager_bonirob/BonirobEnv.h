#ifndef BONIROB_ENV_H
#define BONIROB_ENV_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <boost/algorithm/string.hpp>
#include <std_msgs/String.h>
#include "task_manager_lib/TaskDefinition.h"

// ALL ROS Publishing and subscribing interfaces are defined here.
// Common variables
// Specific to a given platform

namespace task_manager_bonirob {
    class BonirobEnv: public task_manager_lib::TaskEnvironment
    {
        protected:
            ros::Publisher velPub;
            ros::Subscriber poseSub;


            void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
                lastPose = *msg;
            }
            geometry_msgs::PoseStamped lastPose;

        public:
            BonirobEnv(ros::NodeHandle & nh);
            ~BonirobEnv() {};

            const geometry_msgs::PoseStamped & getPose() const {return lastPose;}

            void publishVelocity(double linear, double angular) {
                geometry_msgs::Twist cmd;
                cmd.linear.x = linear;
                cmd.angular.z = angular;
                velPub.publish(cmd);
            }

    };

    typedef boost::shared_ptr<BonirobEnv> BonirobEnvPtr;
    typedef boost::shared_ptr<BonirobEnv const> BonirobEnvConstPtr;
};

#endif // BONIROB_ENV_H
