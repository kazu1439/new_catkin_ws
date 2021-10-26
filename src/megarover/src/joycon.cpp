#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>


geometry_msgs::Twist twist;

void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);


int main(int argc, char** argv)
{
  ros::init(argc, argv, "joycon");

  ros::NodeHandle nh_;
 
  ros::Publisher vel_pub_ = nh_.advertise<geometry_msgs::Twist>("vmegarover/diff_drive_controller/cmd_vel", 1);
  ros::Subscriber joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 1, joyCallback);

  ros::Rate r(10);
  while(nh_.ok()){
    vel_pub_.publish(twist);
    ros::spinOnce();
    r.sleep();
  }
}


void joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  if(joy->buttons[6] == 1){
    twist.angular.z = 2*joy->axes[3];
    twist.linear.x = 2*joy->axes[1];
  }else{
    twist.angular.z = 0;
    twist.linear.x = 0;
  }
  
}