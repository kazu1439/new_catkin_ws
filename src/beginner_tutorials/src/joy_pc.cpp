/**********************************************************************
   File    joy_sample.cpp
   Author  Takahiro Yamazaki
   Environment    ROS_kinetic
   OS       Ubuntu 16.04 LTS
**********************************************************************/
/**********************************************************************
   Problems to be fixed
    -
**********************************************************************/
/**********************************************************************
   Include Libraries
**********************************************************************/

#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include <vector>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"
/**********************************************************************
   Declare variables
**********************************************************************/
#define CYCLE_PERIOD 0.02f
enum MacroesJoyButtons {  //デジタル値
    BUTTONS_SELECT          = 0,    BUTTONS_STICK_LEFT      = 1,
    BUTTONS_STICK_RIGHT     = 2,    BUTTONS_START           = 3,
    BUTTONS_CROSS_UP        = 4,    BUTTONS_CROSS_RIGHT     = 5,
    BUTTONS_CROSS_DOWN      = 6,    BUTTONS_CROSS_LEFT      = 7,
    BUTTONS_L2     = 8,    BUTTONS_R2    = 9,
    BUTTONS_L1     = 10,   BUTTONS_R1    = 11,
    BUTTONS_TRIANGLE = 12,   BUTTONS_CIRCLE   = 13,
    BUTTONS_CROSS    = 14,   BUTTONS_SQUARE   = 15,
    BUTTONS_PAIRING         = 16
};
enum MacroesJoyAxes {               // アナログ値
    AXES_STICK_LEFT_X   =0,    AXES_STICK_LEFT_Y     =1,
    AXES_STICK_RIGHT_X  =2,    AXES_STICK_RIGHT_Y    =3,
    AXES_BUTTON_CROSS_UP        =8,    AXES_BUTTON_CROSS_RIGHT     =9,
    AXES_BUTTON_CROSS_DOWN      =10,    AXES_BUTTON_CROSS_LEFT      =11,
    AXES_BUTTON_L2     =12,    AXES_BUTTON_R2    =13,
    AXES_BUTTON_L1     =14,   AXES_BUTTON_R1    =15,
    AXES_BUTTON_TRIANGLE =16,   AXES_BUTTON_CIRCLE   =17,
    AXES_BUTTON_CROSS    =18,   AXES_BUTTON_SQUARE   =19
};

std::vector<int> JoyButtonsArray( 17, 0 );
std::vector<float> JoyAxesArray( 20, 0.0 );
std_msgs::Float32 a;
/**********************************************************************
   Proto_type_Declare functions
**********************************************************************/
inline void joy_ps3_Callback( const sensor_msgs::Joy::ConstPtr &joy_msg );
inline void v_Callback(const std_msgs::Float32::ConstPtr &msg);
/**********************************************************************
   Main
**********************************************************************/

int main( int argc, char **argv ){
    ros::init( argc, argv, "joy_pc" );
    ros::NodeHandle nh;

    ros::Subscriber sub_first = nh.subscribe( "joy", 1, joy_ps3_Callback );
    ros::Subscriber v = nh.subscribe("v", 1000, v_Callback);

    ros::Publisher pub_float = nh.advertise<std_msgs::Float32>("float", 1000);

    ros::Rate loop_rate( 1.0f/CYCLE_PERIOD );
    while ( ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
        //ROS_INFO("[%f]", JoyAxesArray[0]);
        a.data = JoyAxesArray[0];
        pub_float.publish(a);
    }
    return 0;
}

/**********************************************************************
   Functions
**********************************************************************/

inline void joy_ps3_Callback( const sensor_msgs::Joy::ConstPtr &joy_msg ){
    JoyButtonsArray = joy_msg->buttons;
    JoyAxesArray = joy_msg->axes;
}

inline void v_Callback(const std_msgs::Float32::ConstPtr &msg)
{
  ROS_INFO("[%f]", msg->data);
}