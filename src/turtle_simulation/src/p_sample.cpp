#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

#define CTRL_PERIOD 0.02f

float TurtleX;
float TurtleY;
float TurtleTheta;
float linear_Output = 0.0;
int count = 0;

geometry_msgs::Twist Go;

inline void turtle_Callback(const turtlesim::PoseConstPtr &turtle_msg);
float PID(float target,float position,float delta,float gain);

int main(int argc, char **argv){
    
    ros::init( argc, argv, "p_sample" );
    ros::NodeHandle nh;

    ros::Subscriber sub_turtle = nh.subscribe<turtlesim::Pose>( "turtle1/pose", 1, turtle_Callback );
    ros::Publisher pub_Go = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    
    ros::Rate loop_rate( 1.0f/CTRL_PERIOD );
    while ( ros::ok() ){
        // if(count == 0){
        //     Go.linear.x = PID(10,TurtleX,0.01,2);
        // }
        if(count == 0){
            Go.angular.z = PID(1.57,TurtleTheta,0.001,2);
        }
        else if(count == 1){
            Go.linear.x = PID(10,TurtleY,0.01,2);
        }
        pub_Go.publish(Go);

        ros::spinOnce();
        loop_rate.sleep();
    }
}

inline void turtle_Callback(const turtlesim::PoseConstPtr &turtle_msg){
    TurtleX = turtle_msg->x;
    TurtleY = turtle_msg->y;
    TurtleTheta = turtle_msg->theta;
}

float PID(float target,float position,float delta,float gain){
    if(target-position < delta){
        count++;
        ROS_INFO("Finish");
        return 0;
    }
    else{
        return (target-position)*gain;
    } 
}