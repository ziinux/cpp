
#include "floor_nav/SimTasksEnv.h"
#include <topic_tools/MuxSelect.h>
#include <boost/algorithm/string.hpp>

using namespace floor_nav;

SimTasksEnv::SimTasksEnv(ros::NodeHandle & n) : task_manager_lib::TaskEnvironment(n),
    paused(false), manualControl(false), joystick_topic("/teleop/twistCommand"), auto_topic("/mux/autoCommand"), base_frame("/bubbleRob"), reference_frame("/world"), takeOffRequest(false), takeOffStatus(0), landingRequest(false), landingStatus(0), suctionStatus(0), takeOffOrderStatus(0), landingBackOrderStatus(0)
{
    nh.getParam("joystick_topic",joystick_topic);
    nh.getParam("auto_topic",auto_topic);
    nh.getParam("base_frame",base_frame);
    nh.getParam("reference_frame",reference_frame);

    muxClient = nh.serviceClient<topic_tools::MuxSelect>("/mux/select");


    muxSub = nh.subscribe("/mux/selected",1,&SimTasksEnv::muxCallback,this);
    pointCloud2DSub = nh.subscribe("/vrep/hokuyoSensor",1,&SimTasksEnv::pointCloud2DCallback,this);
    laserscanSub = nh.subscribe("/scan",1,&SimTasksEnv::laserScanCallback,this);
    velPub = nh.advertise<geometry_msgs::Twist>(auto_topic,1);

// ---------------->>>
    takeOffOrderStatusSub = nh.subscribe("/takeOffOrderStatus",1,&SimTasksEnv::takeOffOrderStatusCallback,this);
    landingBackOrderStatusSub = nh.subscribe("/landingBackOrderStatus",1,&SimTasksEnv::landingBackOrderStatusCallback,this);
    setSuctionPub = nh.advertise<std_msgs::Int32>("/vrep/bubblerob/suctionCommand",1);
    suctionStatusSub = nh.subscribe("/vrep/bubblerob/suctionState",1,&SimTasksEnv::suctionStatusCallback,this);
    takeOffRequestSub = nh.subscribe("/takeOffRequest",10,&SimTasksEnv::takeOffRequestCallback,this);
    takeOffStatusSub = nh.subscribe("/takeOffStatus",10,&SimTasksEnv::takeOffStatusCallback,this);
    takeOffAuthorizationPub = nh.advertise<std_msgs::Bool>("/takeOffAuthorization",10);
    landingRequestSub = nh.subscribe("/landingRequest",10,&SimTasksEnv::landingRequestCallback,this);
    landingStatusSub = nh.subscribe("/landingStatus",10,&SimTasksEnv::landingStatusCallback,this);
    landingAuthorizationPub = nh.advertise<std_msgs::Bool>("/landingAuthorization",10);
    posePub = nh.advertise<geometry_msgs::Pose2D>("/ugvPose",10);
    ROI_Sub = nh.subscribe("/ROI",10,&SimTasksEnv::ROI_Callback,this);
    vizMarkersPub = nh.advertise<visualization_msgs::MarkerArray>("/ROI_viz",1);
// ---------------<<<

}

// ---------------->>>
bool SimTasksEnv::isVisited(int id)
{
  bool isVisited = std::find(visitedROI.begin(), visitedROI.end(), id) != visitedROI.end();
  std::cout << "Is " << id << " visited ? " << isVisited << std::endl;
  return isVisited;
}

bool SimTasksEnv::isThereNewROI()
{
    std::map<int, geometry_msgs::PoseStamped>::iterator it;
    if (!ROI.empty())
    {
        for(it = ROI.begin();it != ROI.end(); ++it)
        {
            int id = it->first;
            if( !(std::find(visitedROI.begin(), visitedROI.end(), id) != visitedROI.end()) || (visitedROI.empty()) )
            {
                std::cout << "New ROI found " << id << std::endl;
                std::cout << "is visitedROI empty " << visitedROI.empty() << std::endl;
                return true;
            }
        }
    }
    else
    {
        std::cout << "ROI empty" << std::endl;
    }

    std::cout << "NO ROI found "  << std::endl;
    return false;
}

void SimTasksEnv::setVisited(int id)
{
    visitedROI.push_back(id);
    std::cout << "ROI visited" << id << std::endl;
    for (std::vector<int>::const_iterator it = visitedROI.begin(); it != visitedROI.end(); ++it)   std::cout << *it << ' ';

}
void SimTasksEnv::ROI_Callback(const ar_track_alvar_msgs::AlvarMarkersConstPtr msg)
{
    std::vector<ar_track_alvar_msgs::AlvarMarker> alvarMarkers;
    alvarMarkers = msg->markers;
    if(alvarMarkers.size()>0) insertROI(alvarMarkers);
}

void SimTasksEnv::insertROI(std::vector<ar_track_alvar_msgs::AlvarMarker> alvarMarkers)
{
    for(int i=0;i<alvarMarkers.size();i++)
    {
        int id = alvarMarkers[i].id;
        ROI[id] = alvarMarkers[i].pose;
    }
    update_ROI_viz();
}

void SimTasksEnv::update_ROI_viz()
{
    std::map<int, geometry_msgs::PoseStamped>::iterator it;
    std::vector<visualization_msgs::Marker> vizMarkers;
    for(it = ROI.begin();it != ROI.end(); ++it)
    {
        visualization_msgs::Marker vizMarker;
        vizMarker.header.frame_id = it->second.header.frame_id;
        vizMarker.ns = "basic_shapes";
        vizMarker.type = 1;
        vizMarker.scale.x = 0.5; vizMarker.scale.y = 0.5; vizMarker.scale.z = 0.1;
        if(isVisited(it->first))
        {
            vizMarker.color.r = 0; vizMarker.color.g = 1;vizMarker.color.b = 0;vizMarker.color.a = 1;
        }
        else
        {
            vizMarker.color.r = 1; vizMarker.color.g = 0;vizMarker.color.b = 0;vizMarker.color.a = 1;
        }
        vizMarker.id = it->first;
        vizMarker.pose = it->second.pose;
        vizMarkers.push_back(vizMarker);
       // ROS_INFO("id = %d, x = %f, y = %f",it->first,it->second.position.x,it->second.position.y);
    }
    ROI_viz.markers = vizMarkers;
    vizMarkersPub.publish(ROI_viz);
}


void SimTasksEnv::publishPose2D()
{
    geometry_msgs::Pose2D pose;
    pose = getPose2D();
    posePub.publish(pose);
}


void SimTasksEnv::setSuction(int p_suction)
{
    std_msgs::Int32 suction;
    suction.data = p_suction;
    setSuctionPub.publish(suction);
}

void SimTasksEnv::suctionStatusCallback(const std_msgs::Int32::ConstPtr& msg)
{
    suctionStatus = msg->data;
}

void SimTasksEnv::publishTakeOffAuthorization(bool p_takeOffAuthorization)
{
    std_msgs::Bool takeOffAuthorization;
    takeOffAuthorization.data = p_takeOffAuthorization;
    takeOffAuthorizationPub.publish(takeOffAuthorization);
}

void SimTasksEnv::takeOffRequestCallback(const std_msgs::Bool::ConstPtr& msg)
{
    takeOffRequest = msg->data;
}

void SimTasksEnv::takeOffStatusCallback(const std_msgs::Int16::ConstPtr& msg)
{
    takeOffStatus = msg->data;
}

void SimTasksEnv::publishLandingAuthorization(bool p_landingAuthorization)
{
    std_msgs::Bool landingAuthorization;
    landingAuthorization.data = p_landingAuthorization;
    landingAuthorizationPub.publish(landingAuthorization);
}

void SimTasksEnv::landingRequestCallback(const std_msgs::Bool::ConstPtr& msg)
{
    landingRequest = msg->data;
}

void SimTasksEnv::landingStatusCallback(const std_msgs::Int16::ConstPtr& msg)
{
    landingStatus = msg->data;
}

void SimTasksEnv::takeOffOrderStatusCallback(const std_msgs::Int32::ConstPtr& msg)
{
    takeOffOrderStatus = msg->data;
}

void SimTasksEnv::landingBackOrderStatusCallback(const std_msgs::Int32::ConstPtr& msg)
{
    landingBackOrderStatus = msg->data;
}

// ---------------<<<

void SimTasksEnv::setManualControl()
{
    topic_tools::MuxSelect select;
    select.request.topic = joystick_topic;
    if (!muxClient.call(select)) {
        ROS_ERROR("setManualControl: Failed to call service /mux/select");
    }
}

void SimTasksEnv::setComputerControl()
{
    topic_tools::MuxSelect select;
    select.request.topic = auto_topic;
    if (!muxClient.call(select)) {
        ROS_ERROR("setComputerControl: Failed to call service /mux/select");
    }
}


geometry_msgs::Pose2D SimTasksEnv::getPose2D() const {
    geometry_msgs::Pose2D pose;
    tf::StampedTransform transform;
    try{
        listener.lookupTransform(reference_frame,base_frame, 
                ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
    }
    pose.theta = tf::getYaw(transform.getRotation());
    pose.x = transform.getOrigin().x();
    pose.y = transform.getOrigin().y();
    return pose;
}

geometry_msgs::Pose SimTasksEnv::getPose() const {
    geometry_msgs::Pose pose;
    tf::StampedTransform transform;
    try{
        listener.lookupTransform(reference_frame,base_frame, 
                ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
    }
    tf::quaternionTFToMsg(transform.getRotation(),pose.orientation);
    tf::pointTFToMsg(transform.getOrigin(),pose.position);
    return pose;
}

geometry_msgs::PoseStamped SimTasksEnv::getPoseStamped() const {
    geometry_msgs::PoseStamped pose;
    tf::StampedTransform transform;
    try{
        listener.lookupTransform(reference_frame,base_frame, 
                ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
    }
    tf::quaternionTFToMsg(transform.getRotation(),pose.pose.orientation);
    tf::pointTFToMsg(transform.getOrigin(),pose.pose.position);
    pose.header.stamp = transform.stamp_;
    return pose;
}

void SimTasksEnv::publishVelocity(double linear, double angular) {
    geometry_msgs::Twist cmd;
    if (paused) {
        cmd.linear.x = 0.;
        cmd.angular.z = 0.;
    } else {
        cmd.linear.x = linear;
        cmd.angular.z = angular;
    }
    velPub.publish(cmd);
}

void SimTasksEnv::muxCallback(const std_msgs::String::ConstPtr& msg) {
    if (msg->data == joystick_topic) {
        manualControl = true;
    } else if (msg->data == auto_topic) {
        manualControl = false;
    } else {
        ROS_ERROR("Received unknown mux selection: '%s'",msg->data.c_str());
    }
}

void SimTasksEnv::pointCloud2DCallback(const sensor_msgs::PointCloud2ConstPtr msg) {
    pcl::fromROSMsg(*msg, pointCloud2D);
}

void SimTasksEnv::laserScanCallback(const sensor_msgs::LaserScanConstPtr msg) {
    pointCloud2D.resize(msg->ranges.size());
    for (size_t i=0;i<msg->ranges.size();i++) {
        pointCloud2D[i].x = msg->ranges[i]*cos(msg->angle_min + i*msg->angle_increment);
        pointCloud2D[i].y = msg->ranges[i]*sin(msg->angle_min + i*msg->angle_increment);
    }
}

