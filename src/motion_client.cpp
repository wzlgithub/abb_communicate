#include "motion_state.h"
#include <ros/ros.h>
#include <iostream>
#include <geometry_msgs/Pose.h>
#include "abb_communicate/robot_move_request.h"

using namespace std;

class robot_motion       
{
public:
    robot_motion(ros::NodeHandle& n);
    ~robot_motion();

private:
    MotionState move_client;
    ros::NodeHandle nh_;
    ros::ServiceServer move_requset_server;
    bool robot_move_request(abb_communicate::robot_move_request::Request& target_pose,
                            abb_communicate::robot_move_request::Response& move_res);
};

robot_motion::robot_motion(ros::NodeHandle& n):nh_(n)
{
    move_client.setup_connect(2700,"192.168.125.1");
    move_requset_server=nh_.advertiseService("robot_move_request",&robot_motion::robot_move_request,this);
}

robot_motion::~robot_motion()
{
    move_client.close_connect();
}

bool robot_motion::robot_move_request(abb_communicate::robot_move_request::Request& req, 
                                            abb_communicate::robot_move_request::Response& res)
{
    vector<float> target_pose_exe;
    target_pose_exe.push_back(req.target_pose.position.x);
    target_pose_exe.push_back(req.target_pose.position.y);
    target_pose_exe.push_back(req.target_pose.position.z);
    target_pose_exe.push_back(req.target_pose.orientation.x);
    target_pose_exe.push_back(req.target_pose.orientation.y);
    target_pose_exe.push_back(req.target_pose.orientation.z);
    target_pose_exe.push_back(req.target_pose.orientation.w);


    bool move_res=move_client.set_move_request(1,target_pose_exe);
    if(move_res)
        res.move_res=true;
    else
        res.move_res=false;
    return true;
}







int main()
{
    ros::NodeHandle n;
    robot_motion rm(n);
    ros::spin();
    return 0;
}
