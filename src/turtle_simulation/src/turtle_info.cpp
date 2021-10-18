#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

#define CYCLE_PERIOD 0.02f

inline void TI_Callback(const turtlesim::Pose::ConstPtr &TI_msg);

int main( int argc, char **argv ){
    ros::init( argc, argv, "turtle_info" );
    ros::NodeHandle nh;

    ros::Subscriber sub_TI = nh.subscribe<turtlesim::Pose>( "turtle1/pose", 1, TI_Callback );

    ros::Rate loop_rate( 1.0f/CYCLE_PERIOD );
    while ( ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

inline void TI_Callback(const turtlesim::Pose::ConstPtr &TI_msg)
{
  ROS_INFO("x:[%f]",TI_msg->x);
  ROS_INFO("y:[%f]",TI_msg->y);
  ROS_INFO("theta:[%f]",TI_msg->theta);
  ROS_INFO("linear_velocity:[%f]",TI_msg->linear_velocity);
  ROS_INFO("angular_velocity:[%f]",TI_msg->angular_velocity);
}