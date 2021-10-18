#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <std_msgs/Bool.h>

#define CTRL_PERIOD 0.02f

float target = 10;
float TurtleX;
float linear_Output = 0.0;
bool startFlag = false;
geometry_msgs::Twist Go;

inline void turtle_Callback(const turtlesim::PoseConstPtr &turtle_msg);
inline void start_Callback(const std_msgs::Bool::ConstPtr &start_msg);

int main(int argc, char **argv){
    
    ros::init( argc, argv, "turtle_p" );
    ros::NodeHandle nh;

    ros::Subscriber sub_turtle = nh.subscribe<turtlesim::Pose>( "turtle1/pose", 1, turtle_Callback );
    ros::Subscriber sub_start = nh.subscribe<std_msgs::Bool>( "start", 1, start_Callback );
    ros::Publisher pub_Go = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    
    ros::Rate loop_rate( 1.0f/CTRL_PERIOD );
    while ( ros::ok() ){
        ROS_INFO("[%f]",target-TurtleX);
        if(target-TurtleX > 0.001){
            linear_Output = target-TurtleX;
            //linear_Output = linear_Output*0.1;
        }
        else{
            linear_Output = 0;
            ROS_INFO("Finish");
            break;
        }
        Go.linear.x = linear_Output;

        if(startFlag){
            pub_Go.publish(Go);
            //ROS_INFO("[%f]",linear_Output);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }
}

inline void turtle_Callback(const turtlesim::PoseConstPtr &turtle_msg){
    TurtleX = turtle_msg->x;
}

inline void start_Callback(const std_msgs::Bool::ConstPtr &start_msg){
    startFlag = start_msg->data;
}