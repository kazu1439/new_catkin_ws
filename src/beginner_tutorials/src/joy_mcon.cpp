//#include "mbed.h"
//#include "ros.h"
#include "ros/ros.h"
//#include <sensor_msgs/Joy.h>
//#include <vector>
//#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float32.h"
//#include "std_msgs/Bool.h"
//#include <std_msgs/Int32MultiArray.h>
//#include "dc_motor_1.h"
#define CTRL_PERIOD 0.02f

float float_msg = 0;
//Timer ControlTicker;
//dc_motor_1 Motor0( D3, D8, 0 );
std_msgs::Float32 v;

inline void joy_Callback(const std_msgs::Float32 &msg);

//ros::Publisher                      v_pub("v", &v);
//ros::Subscriber <std_msgs::Float32> float_sub("float", &joy_Callback);


int main(int argc, char **argv)
{
    ros::init( argc, argv, "joy_mcon" );
    ros::NodeHandle n;
    ros::Publisher pub_v = n.advertise<std_msgs::Float32>("v", 1000);
    ros::Subscriber sub_float = n.subscribe("float", 1000, joy_Callback);
    ros::Rate loop_rate( 1.0f/CTRL_PERIOD );
    //n.getHardware()->setBaud(115200);
    //n.initNode();
    //n.advertise(v_pub);
    //n.subscribe(float_sub);

    for(;; ){
        //if ( ControlTicker.read() >= CTRL_PERIOD ){
        //    ControlTicker.reset();
        //    //Motor0.drive(float_msg*10);
        //    
        //    v.data = float_msg*10;
        //    pub_v.publish(v);
        //    n.spinOnce();
        //    }
        while ( ros::ok()){
            ros::spinOnce();
            loop_rate.sleep();
            //ROS_INFO("[%f]", JoyAxesArray[0]);
            v.data = float_msg*10;
            pub_v.publish(v);
        }  
    }
}

inline void joy_Callback(const std_msgs::Float32 &msg)
{
  float_msg = msg.data;
}