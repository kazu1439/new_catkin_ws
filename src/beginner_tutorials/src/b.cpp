#include "ros/ros.h"
#include <std_msgs/Int32MultiArray.h>


void chatterCallback(const std_msgs::Int32MultiArray::ConstPtr& msg)
{
  ROS_INFO("%i:%i:%i", msg->data[0],msg->data[1],msg->data[2]);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "b");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("msg", 1000, chatterCallback);
  ros::spin();

  return 0;
}