#include "ros/ros.h"
#include <std_msgs/Int32.h>

#define CTRL_PERIOD 0.02f

int num;
bool input_num = false;

inline void Number_Callback(const std_msgs::Int32::ConstPtr &int_msg);

int main(int argc, char **argv){
    
    ros::init( argc, argv, "check_num" );
    ros::NodeHandle nh;

    ros::Subscriber sub_start = nh.subscribe<std_msgs::Int32>( "number", 1, Number_Callback );
    
    ros::Rate loop_rate( 1.0f/CTRL_PERIOD );
    while ( ros::ok() ){
        if(input_num){
            if(num == 0){
                ROS_INFO("This is zero.");
            }
            else if(num == 1){
                ROS_INFO("This is one.");
            }
            else{
                ROS_INFO("Neither");
            }
            input_num = false;
        }
        
        ros::spinOnce();
        loop_rate.sleep();
    }
}

inline void Number_Callback(const std_msgs::Int32::ConstPtr &int_msg){
    num = int_msg->data;
    input_num = true;
}