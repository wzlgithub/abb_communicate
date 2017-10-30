#include "motion_state.h"
#include <ros/ros.h>
#include <iostream>
#include <geometry_msgs/Pose.h>

using namespace std;
class robot_state       
{
public:
    robot_state(ros::NodeHandle& n);
    ~robot_state();
    void publish_state();
private:
    MotionState state_client;
    ros::NodeHandle nh_;
    ros::Publisher robot_state_publisher;
};


robot_state::robot_state(ros::NodeHandle& n):nh_(n)
{
    state_client.setup_connect(2700,"192.168.125.1");
    robot_state_publisher=nh_.advertise<geometry_msgs::Pose>("robot_communication/robot_state",2);
}

robot_state::~robot_state()
{
    state_client.close_connect();
}

void robot_state::publish_state()
{
    vector<float> current_state(7);
    state_client.get_current_state(2,current_state);
    geometry_msgs::Pose pose;
    pose.position.x=current_state[0];
    pose.position.y=current_state[1];
    pose.position.z=current_state[2];
    pose.orientation.x=current_state[3];
    pose.orientation.y=current_state[4];
    pose.orientation.z=current_state[5];
    pose.orientation.w=current_state[6];
    robot_state_publisher.publish(pose);

}
int main()
{
    ros::NodeHandle n;
    robot_state rs(n);
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
      rs.publish_state();
      ros::spinOnce();
      loop_rate.sleep();
    }
      
    return 0;
}
