
#include "task_manager_uavsim/UAVEnv.h"

using namespace task_manager_uavsim;

UAVEnv::UAVEnv(ros::NodeHandle & n) : task_manager_lib::TaskEnvironment(n),
    base_frame("/bubbleRob"), reference_frame("/world"), takeOffAuthorization(false), landingAuthorization(false), motorState(false), batteryLevel(100.0)
{
    sleep(1);
    velPub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);

    // ---------------->>>
    batteryLevelSub = nh.subscribe("/uav/batteryLevel",10,&UAVEnv::batteryLevelCallback,this);
    setMotorPub = nh.advertise<std_msgs::Int32>("/vrep/drone/motor_on",1);
    motorStateSub = nh.subscribe("/vrep/drone/motor_state",1,&UAVEnv::motorStateCallback,this);
    ugvPoseSub = nh.subscribe("/ugvPose",10,&UAVEnv::ugvPoseCallback,this);
    landingStatusPub = nh.advertise<std_msgs::Int16>("/landingStatus",1);
    landingRequestPub = nh.advertise<std_msgs::Bool>("/landingRequest",1);
    landingAuthorizationSub = nh.subscribe("/landingAuthorization",10,&UAVEnv::landingAuthorizationCallback,this);
    takeOffStatusPub = nh.advertise<std_msgs::Int16>("/takeOffStatus",1);
    takeOffRequestPub = nh.advertise<std_msgs::Bool>("/takeOffRequest",1);
    takeOffAuthorizationSub = nh.subscribe("/takeOffAuthorization",10,&UAVEnv::takeOffAuthorizationCallback,this);
    visMarkersPub = nh.advertise<visualization_msgs::MarkerArray>("/ROI_vis",1);
    ROI_pub = nh.advertise<ar_track_alvar_msgs::AlvarMarkers>("/ROI",1);
    poseMarkerSub = nh.subscribe("/ar_pose_marker",1,&UAVEnv::poseMarker_cb,this);

    // ----------------<<<
 
    nh.getParam("base_frame",base_frame);
    nh.getParam("reference_frame",reference_frame);
}

// ---------------->>>
void UAVEnv::poseMarker_cb(const ar_track_alvar_msgs::AlvarMarkersConstPtr msg) 
{
    std::vector<ar_track_alvar_msgs::AlvarMarker> alvarMarkers;
    alvarMarkers = msg->markers;
    if(alvarMarkers.size()>0) insertROI(alvarMarkers);
    //ROS_INFO("x = %f, y = %f, theta = %f",pose.position.x,pose.position.y,(pose.orientation.z*2*180.0/3.1415));
}


void UAVEnv::insertROI(std::vector<ar_track_alvar_msgs::AlvarMarker> alvarMarkers)
{
    //geometry_msgs::Pose pose = getPose();
    geometry_msgs::PoseStamped pose_worldFrame;
    geometry_msgs::PoseStamped pose_CameraFrame;

    for(int i=0;i<alvarMarkers.size();i++)
    {
        //ROS_INFO("id = %d, x = %f, y = %f",alvarMarkers[i].id,alvarMarkers[i].pose.pose.position.x,alvarMarkers[i].pose.pose.position.y);}
        int id = alvarMarkers[i].id;
        pose_CameraFrame = alvarMarkers[i].pose;
        pose_CameraFrame.header.frame_id = alvarMarkers[i].header.frame_id;
        //pose_CameraFrame.header.frame_id = "ar_marker_13";
        listener.transformPose(reference_frame,pose_CameraFrame,pose_worldFrame);
//        std::cout << pose_worldFrame.header.frame_id << std::endl;
        ROI[id] = pose_worldFrame;
    }
    update_ROI_msg();
}

void UAVEnv::update_ROI_msg()
{
    std::map<int, geometry_msgs::PoseStamped>::iterator it;
    std::vector<ar_track_alvar_msgs::AlvarMarker> alvarMarkers;
    std::vector<visualization_msgs::Marker> visMarkers;
    for(it = ROI.begin();it != ROI.end(); ++it)
    {
        ar_track_alvar_msgs::AlvarMarker alvarMarker;
        visualization_msgs::Marker visMarker;
        visMarker.header.frame_id = it->second.header.frame_id;
        visMarker.ns = "basic_shapes";
        visMarker.type = 1;
        visMarker.scale.x = 0.5; visMarker.scale.y = 0.5; visMarker.scale.z = 0.1;
        visMarker.color.r = 1; visMarker.color.g = 0;visMarker.color.b = 0;visMarker.color.a = 1;
        alvarMarker.id = it->first;
        visMarker.id = it->first;
        alvarMarker.pose = it->second;
        visMarker.pose = it->second.pose;
        alvarMarkers.push_back(alvarMarker);
        visMarkers.push_back(visMarker);
       // ROS_INFO("id = %d, x = %f, y = %f",it->first,it->second.position.x,it->second.position.y);
    }
    ROI_msg.markers = alvarMarkers;
    ROI_vis.markers = visMarkers;    
    visMarkersPub.publish(ROI_vis);
    ROI_pub.publish(ROI_msg);
}

void UAVEnv::publishLandingRequest(bool p_request)
{
    std_msgs::Bool request;
    request.data = p_request;
    landingRequestPub.publish(request);
}

void UAVEnv::publishLandingStatus(int p_landingStatus)
{
    std_msgs::Int16 landingStatus;
    landingStatus.data = p_landingStatus;
    landingStatusPub.publish(landingStatus);
}

void UAVEnv::batteryLevelCallback(const std_msgs::Float64::ConstPtr& msg)
{
    batteryLevel = msg->data;
}

void UAVEnv::motorStateCallback(const std_msgs::Int32::ConstPtr& msg)
{
    motorState = (msg->data<=0)? false : true ;
}

void UAVEnv::setMotorON(bool p_motorON)
{
    std_msgs::Int32 motorON;
    motorON.data = (p_motorON)? 2 : 0 ;
    setMotorPub.publish(motorON);
}

void UAVEnv::ugvPoseCallback(const geometry_msgs::Pose2D::ConstPtr& msg)
{
    ugvPose = *msg;
}

void UAVEnv::landingAuthorizationCallback(const std_msgs::Bool::ConstPtr& msg)
{
    landingAuthorization = msg->data;
}

void UAVEnv::publishTakeOffRequest(bool p_request)
{
    std_msgs::Bool request;
    request.data = p_request;
    takeOffRequestPub.publish(request);
}

void UAVEnv::publishTakeOffStatus(int p_takeOffStatus)
{
    std_msgs::Int16 takeOffStatus;
    takeOffStatus.data = p_takeOffStatus;
    takeOffStatusPub.publish(takeOffStatus);
}

void UAVEnv::takeOffAuthorizationCallback(const std_msgs::Bool::ConstPtr& msg)
{
    takeOffAuthorization = msg->data;
}

// ----------------<<<

geometry_msgs::Pose2D UAVEnv::getPose2D() const {
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

geometry_msgs::Pose UAVEnv::getPose() const {
    geometry_msgs::Pose pose;
    tf::StampedTransform transform;
    try{
        listener.lookupTransform(reference_frame,base_frame, 
                ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
    }
    // tf::Quaternion q = transform.getRotation();
    // printf("From %s to %s: %f %f %f %f\n",reference_frame.c_str(),
    //         base_frame.c_str(),q.x(),q.y(),q.z(),q.w());
    tf::quaternionTFToMsg(transform.getRotation(),pose.orientation);
    tf::pointTFToMsg(transform.getOrigin(),pose.position);
    return pose;
}

geometry_msgs::PoseStamped UAVEnv::getPoseStamped() const {
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

