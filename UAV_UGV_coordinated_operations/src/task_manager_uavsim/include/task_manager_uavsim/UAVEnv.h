#ifndef UAV_ENV_H
#define UAV_ENV_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <boost/algorithm/string.hpp>
#include <std_msgs/String.h>
#include "task_manager_lib/TaskDefinition.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Pose2D.h"
#include <map>
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "visualization_msgs/MarkerArray.h"
#include "visualization_msgs/Marker.h"

namespace task_manager_uavsim {
    class UAVEnv: public task_manager_lib::TaskEnvironment
    {
        protected:
// ---------------->>>

            ros::Subscriber poseMarkerSub;
            ros::Subscriber batteryLevelSub;
            ros::Subscriber motorStateSub;
            ros::Subscriber ugvPoseSub;
            ros::Subscriber takeOffAuthorizationSub;
            ros::Subscriber landingAuthorizationSub;
            ros::Publisher setMotorPub;
            ros::Publisher takeOffRequestPub;
            ros::Publisher landingRequestPub;
            ros::Publisher takeOffStatusPub;
            ros::Publisher landingStatusPub;
            ros::Publisher visMarkersPub;
            ros::Publisher ROI_pub;

            void poseMarker_cb(const ar_track_alvar_msgs::AlvarMarkersConstPtr msg);
            void batteryLevelCallback(const std_msgs::Float64::ConstPtr& msg);
            void motorStateCallback(const std_msgs::Int32::ConstPtr& msg);
            void ugvPoseCallback(const geometry_msgs::Pose2D::ConstPtr& msg);
            void takeOffAuthorizationCallback(const std_msgs::Bool::ConstPtr& msg);
            void landingAuthorizationCallback(const std_msgs::Bool::ConstPtr& msg);
            bool takeOffAuthorization;
            bool landingAuthorization;
            bool motorState;
            float batteryLevel; // prctg 0.0 to 100.0
            geometry_msgs::Pose2D ugvPose;
            std::map <int,geometry_msgs::PoseStamped> ROI;
            ar_track_alvar_msgs::AlvarMarkers ROI_msg;
            visualization_msgs::MarkerArray ROI_vis;
// ----------------<<<

            ros::Publisher velPub;
            tf::TransformListener listener;

            std::string base_frame;
            std::string reference_frame;

        public:
            UAVEnv(ros::NodeHandle & nh);
            ~UAVEnv() {};

            geometry_msgs::Pose2D getPose2D() const ; 

            geometry_msgs::Pose getPose() const ;

            geometry_msgs::PoseStamped getPoseStamped() const;

            void publishTwist(double xvel, double yvel, double yawvel, double z_altitude=-1) {
                geometry_msgs::Twist cmd;
                cmd.linear.x = xvel;
                cmd.linear.y = yvel;
                cmd.linear.z = z_altitude;
                cmd.angular.z = yawvel;
                velPub.publish(cmd);
            }
// ---------------->>
            void publishTakeOffRequest(bool request);
            void publishLandingRequest(bool request);
            void publishTakeOffStatus(int p_takeOffStatus);
            void publishLandingStatus(int p_landingStatus);
            void setMotorON(bool p_motorON);
            void insertROI(std::vector<ar_track_alvar_msgs::AlvarMarker>);
            void update_ROI_msg();
            geometry_msgs::Pose2D getUGVPose() const {return ugvPose;}
            bool getTakeOffAuthorization() const {return takeOffAuthorization;}
            bool getLandingAuthorization() const {return landingAuthorization;}
            bool isMotorON() const {return motorState;}
            float getBatteryLevel() {return batteryLevel;}
            ar_track_alvar_msgs::AlvarMarkers get_ROI_msg() {return ROI_msg;}
// ----------------<<
    };

    typedef boost::shared_ptr<UAVEnv> UAVEnvPtr;
    typedef boost::shared_ptr<UAVEnv const> UAVEnvConstPtr;
};

#endif // UAV_ENV_H
