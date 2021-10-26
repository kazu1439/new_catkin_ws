#include "ros/ros.h"
#include <std_msgs/Int32MultiArray.h>

int count = 0;
std_msgs::Int32MultiArray msg;

int s(int time_count);
int m(int time_count);
int h(int time_count);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "timer");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int32MultiArray>("time", 1000);

  ros::Rate loop_rate(10);
  
  while (ros::ok())
  {
    msg.data.resize(3);
    msg.data[2] = s(count);
    msg.data[1] = m(count);
    msg.data[0] = h(count);
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}

int s(int time_count){
  int times = time_count/600;
  int sec = (time_count - 600*times)/10;
  return sec;
}

int m(int time_count){
  int times = time_count/36000;
  int min = (time_count - 36000*times)/600;
  return min;
}

int h(int time_count){
  int times = time_count/864000;
  int hour = (time_count - 864000*times)/36000;
  return hour;
}