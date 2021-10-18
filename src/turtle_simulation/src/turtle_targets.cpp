#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include <vector>
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <math.h>

#define CYCLE_PERIOD 0.02f

geometry_msgs::Twist turtle_msg;
float TurtleX,TurtleY,TurtleTheta,target_theta;
int last_L1,last_R1;
int target_now = 0;
bool target_check = false;
bool theta_check = false;
int running = 1;

int target_num = 19;
float targets[19][2] = {
    {5.5,10.0},
    {10.0,10.0},
    {10.0,1.0},
    {5.5,1.0},
    {5.5,5.5},
    {5.5,7},
    {6.5,3},
    {3.5,5},
    {7.5,5},
    {4.5,3},
    {5.5,7},
    {7.5,5},
    {6.5,3},
    {4.5,3},
    {3.5,5},
    {5.5,7},
    {5.5,1},
    {1,1},
    {1,10},
};


inline void TI_Callback(const turtlesim::PoseConstPtr &TI_msg);
inline void running_Callback( const std_msgs::Int32::ConstPtr &running_msg);

int main( int argc, char **argv ){
    ros::init( argc, argv, "turtle_targets" );
    ros::NodeHandle nh;

    ros::Subscriber sub_TI = nh.subscribe<turtlesim::Pose>( "turtle1/pose", 1, TI_Callback );
    ros::Subscriber sub_running = nh.subscribe( "running", 1, running_Callback);

    ros::Publisher pub_turtle = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

    ros::Rate loop_rate( 1.0f/CYCLE_PERIOD );
    while ( ros::ok() ){
        if(theta_check == false){
            if((targets[target_now][0]-TurtleX) < 0){
                if((targets[target_now][1]-TurtleY) > 0){
                    target_theta = atan((targets[target_now][1]-TurtleY)/(targets[target_now][0]-TurtleX))+3.14;
                }
                else{
                    target_theta = atan((targets[target_now][1]-TurtleY)/(targets[target_now][0]-TurtleX))-3.14;
                }
            }
            else{
                target_theta = atan((targets[target_now][1]-TurtleY)/(targets[target_now][0]-TurtleX));
            }
            if(fabsf(target_theta-TurtleTheta) <= 3.14){
                turtle_msg.angular.z = 2*fabsf(target_theta-TurtleTheta);
            }
            if(fabsf(target_theta-TurtleTheta) > 3.14){
                turtle_msg.angular.z = 2*(6.28-fabsf(target_theta-TurtleTheta));
            }
        }
        if(fabsf(target_theta-TurtleTheta) < 0.001 || TurtleTheta-target_theta > 6.279){
            turtle_msg.angular.z = 0;
            theta_check = true;
        }
        if(theta_check == true){
            turtle_msg.linear.x = 1.5*(pow(TurtleX-targets[target_now][0],2)+pow(TurtleY-targets[target_now][1],2));
        }
        if(pow(TurtleX-targets[target_now][0],2)+pow(TurtleY-targets[target_now][1],2) < 0.001){
            turtle_msg.linear.x = 0;
            target_check = true;
        }
        if(target_check == true){
            target_now += 1;
            if(target_now == target_num){
                target_now = 0;
            }
            target_check = false;
            theta_check = false;
        }
        if(running == 1){
            pub_turtle.publish(turtle_msg);
        }

        ros::spinOnce();
        loop_rate.sleep();
        
    }
    return 0;
}

inline void TI_Callback(const turtlesim::PoseConstPtr &TI_msg)
{
  TurtleX = TI_msg->x;
  TurtleY = TI_msg->y;
  TurtleTheta = TI_msg->theta;
}

inline void running_Callback( const std_msgs::Int32::ConstPtr &running_msg ){
    running = running_msg->data;
}