#ifndef SIM_TASKS_ENV_H
#define SIM_TASKS_ENV_H

#include <ros/ros.h>
#include "task_manager_lib/TaskDefinition.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int32.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/PoseStamped.h"
#include "sensor_msgs/LaserScan.h"
#include "pcl_ros/point_cloud.h"
#include "pcl/point_types.h"
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "visualization_msgs/MarkerArray.h"
#include "visualization_msgs/Marker.h"
#include <algorithm>

namespace floor_nav {
    class SimTasksEnv: public task_manager_lib::TaskEnvironment
    {
        protected:
            bool paused;
            ros::Subscriber muxSub;
            ros::Subscriber pointCloud2DSub;
            ros::Subscriber laserscanSub;
            ros::Publisher velPub;
            ros::ServiceClient muxClient;
            tf::TransformListener listener;

            void muxCallback(const std_msgs::String::ConstPtr& msg) ;

            void pointCloud2DCallback(const sensor_msgs::PointCloud2ConstPtr msg) ;
            void laserScanCallback(const sensor_msgs::LaserScanConstPtr msg) ;

// ---------------->>>
            ros::Subscriber ROI_Sub;
            ros::Subscriber takeOffOrderStatusSub;
            ros::Subscriber landingBackOrderStatusSub;
            ros::Subscriber takeOffRequestSub;
            ros::Subscriber takeOffStatusSub;
            ros::Publisher takeOffAuthorizationPub;
            ros::Subscriber landingRequestSub;
            ros::Subscriber landingStatusSub;
            ros::Publisher landingAuthorizationPub;
            ros::Publisher posePub;
            ros::Publisher setSuctionPub;
            ros::Subscriber suctionStatusSub;
            ros::Publisher vizMarkersPub;

            void ROI_Callback(const ar_track_alvar_msgs::AlvarMarkersConstPtr msg);
            void takeOffRequestCallback(const std_msgs::Bool::ConstPtr& msg) ;
            void takeOffStatusCallback(const std_msgs::Int16::ConstPtr& msg) ;
            void landingRequestCallback(const std_msgs::Bool::ConstPtr& msg) ;
            void landingStatusCallback(const std_msgs::Int16::ConstPtr& msg) ;
            void suctionStatusCallback(const std_msgs::Int32::ConstPtr& msg) ;
            void takeOffOrderStatusCallback(const std_msgs::Int32::ConstPtr& msg);
            void landingBackOrderStatusCallback(const std_msgs::Int32::ConstPtr& msg);
            bool takeOffRequest;
            bool landingRequest;
            int takeOffStatus;
            int landingStatus;
            int suctionStatus;
            int takeOffOrderStatus;
            int landingBackOrderStatus;
            std::map <int,geometry_msgs::PoseStamped> ROI;
            visualization_msgs::MarkerArray ROI_viz;
            std::vector<int> visitedROI;
// ----------------<<<
            
            bool manualControl;
            std::string joystick_topic;
            std::string auto_topic;
            std::string base_frame;
            std::string reference_frame;
            pcl::PointCloud<pcl::PointXYZ> pointCloud;
            pcl::PointCloud<pcl::PointXYZ> pointCloud2D;

        public:
            SimTasksEnv(ros::NodeHandle & nh);
            ~SimTasksEnv() {};

            ros::NodeHandle & getNodeHandle() {return nh;}

// ---------------->>>
            bool isThereNewROI();
            bool isVisited(int id);
            void setVisited(int id);
            void update_ROI_viz();
            void insertROI(std::vector<ar_track_alvar_msgs::AlvarMarker> alvarMarkers);
            void setSuction(int p_suction);
            void publishTakeOffAuthorization(bool p_takeOffAuthorization);
            void publishLandingAuthorization(bool p_landingAuthorization);
            void publishPose2D(); 
            std::map <int,geometry_msgs::PoseStamped> getROI() const {return ROI;}
            bool getTakeOffRequest() const {return takeOffRequest;}
            int getTakeOffStatus() const {return takeOffStatus;}
            bool getLandingRequest() const {return landingRequest;}
            int getLandingStatus() const {return landingStatus;}
            int getSuctionStatus() const {return suctionStatus;}
            int getTakeOffOrderStatus() const {return takeOffOrderStatus;}
            void setTakeOffOrderStatus(int p_orderStatus) {takeOffOrderStatus = p_orderStatus;}
            int getLandingBackOrderStatus() const {return landingBackOrderStatus;}
	    void setLandingBackOrderStatus(int p_orderStatus) {landingBackOrderStatus = p_orderStatus;}
// ----------------<<<

            geometry_msgs::Pose2D getPose2D() const ; 

            geometry_msgs::Pose getPose() const ;

            geometry_msgs::PoseStamped getPoseStamped() const  ;

            const pcl::PointCloud<pcl::PointXYZ>& getPointCloud2D() const {return pointCloud2D;}

            void publishVelocity(double linear, double angular) ;

            void setManualControl();
            void setComputerControl();
            bool getManualControl() const {return manualControl;}

        public: // To make point cloud work on 32bit system
            EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    };

};

#endif // SIM_TASKS_ENV_H
