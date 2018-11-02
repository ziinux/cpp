#ifndef UAV_ENV_H
#define UAV_ENV_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <boost/algorithm/string.hpp>
#include <std_msgs/String.h>
#include "task_manager_lib/TaskDefinition.h"

namespace task_manager_uav {
    class UAVEnv: public task_manager_lib::TaskEnvironment
    {
        protected:
            ros::Publisher velPub;
            ros::Subscriber poseSub;


            void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
                lastPose = *msg;
            }
            geometry_msgs::PoseStamped lastPose;

        public:
            UAVEnv(ros::NodeHandle & nh);
            ~UAVEnv() {};

            const geometry_msgs::PoseStamped & getPose() const {return lastPose;}

            void publishVelocity(double linear, double angular) {
                geometry_msgs::Twist cmd;
                cmd.linear.x = linear;
                cmd.angular.z = angular;
                velPub.publish(cmd);
            }

    };

    typedef boost::shared_ptr<UAVEnv> UAVEnvPtr;
    typedef boost::shared_ptr<UAVEnv const> UAVEnvConstPtr;
};

#endif // UAV_ENV_H
