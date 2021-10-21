#include "ros/ros.h"
#include <std_msgs/Int32MultiArray.h>


std_msgs::Int32MultiArray msg;


int main(int argc, char **argv)
{
  ros::init(argc, argv, "a");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int32MultiArray>("msg", 1000);

  ros::Rate loop_rate(10);
  msg.data.resize(3);
  while (ros::ok())
  {
    msg.data[2] = 9;
    msg.data[1] = 3;
    msg.data[0] = 2002;
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
