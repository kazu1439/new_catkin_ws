#include "turtle_simulation/lpf.h"
#include "turtle_simulation/pid.h"
#include "turtle_simulation/differential.h"
#include "turtle_simulation/integral.h"
#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

#define CTRL_PERIOD 0.02f

float target=1.57;
float first_pos=0.0;
float TurtleX,TurtleY,TurtleTheta;
bool a = false;
geometry_msgs::Twist turtle_msg;

void pid_init(void);                                 //********１

LPF lpf_0( CTRL_PERIOD, 0.3 );
PID pid( CTRL_PERIOD );

inline void TI_Callback(const turtlesim::PoseConstPtr &TI_msg);

int main(int argc, char **argv){
    
    ros::init( argc, argv, "turtle_p" );
    ros::NodeHandle nh;

    ros::Subscriber sub_TI = nh.subscribe<turtlesim::Pose>( "turtle1/pose", 1, TI_Callback );

    ros::Publisher pub_turtle = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    float linear_Output = 0.0;
    float angular_Output = 0.0;
    
    pid_init();
    ros::Rate loop_rate( 1.0f/CTRL_PERIOD );
    while ( ros::ok() ){
        
        if(a == false){
            if(pid.checkEnd() == 1 ){
                angular_Output = pid.control( TurtleTheta );
            }
            else{
                angular_Output = 0.0f;
                linear_Output = 0.0f;
                a = true;
                target = 10;
                first_pos = 5.5;
                pid_init();
                ROS_INFO("linear:[%f],angular[%f]",linear_Output,angular_Output);               
            }
        }
        else{
            if(pid.checkEnd() == 1 ){
                linear_Output = pid.control( TurtleY );
            }
            else{
                angular_Output = 0.0f;
                linear_Output = 0.0f;
                ROS_INFO("linear:[%f],angular[%f]",linear_Output,angular_Output);               
            }
        }
        
        
        
        turtle_msg.linear.x = linear_Output;
        turtle_msg.angular.z = angular_Output;
        pub_turtle.publish(turtle_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}//main

void pid_init()                               //********１
{
  pid.reset();
  pid.setTarget(target);
  pid.setGain(2.0,0.0,0.0);
  pid.setEndStatus(0.01,0.01);
  pid.setFirstPosition(first_pos);
}


inline void TI_Callback(const turtlesim::PoseConstPtr &TI_msg)
{
  TurtleX = TI_msg->x;
  TurtleY = TI_msg->y;
  TurtleTheta = TI_msg->theta;
}