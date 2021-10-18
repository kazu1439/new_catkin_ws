#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include <vector>
#include "std_msgs/Int32.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>


#define CYCLE_PERIOD 0.02f
//enum MacroesJoyButtons {  //デジタル値
//    BUTTONS_SELECT          = 0,    BUTTONS_STICK_LEFT      = 1,
//    BUTTONS_STICK_RIGHT     = 2,    BUTTONS_START           = 3,
//    BUTTONS_CROSS_UP        = 4,    BUTTONS_CROSS_RIGHT     = 5,
//    BUTTONS_CROSS_DOWN      = 6,    BUTTONS_CROSS_LEFT      = 7,
//    BUTTONS_L2     = 8,    BUTTONS_R2    = 9,
//    BUTTONS_L1     = 10,   BUTTONS_R1    = 11,
//    BUTTONS_TRIANGLE = 12,   BUTTONS_CIRCLE   = 13,
//    BUTTONS_CROSS    = 14,   BUTTONS_SQUARE   = 15,
//    BUTTONS_PAIRING         = 16
//};
//enum MacroesJoyAxes {               // アナログ値
//    AXES_STICK_LEFT_X   =0,    AXES_STICK_LEFT_Y     =1,
//    AXES_STICK_RIGHT_X  =2,    AXES_STICK_RIGHT_Y    =3,
//    AXES_BUTTON_CROSS_UP        =8,    AXES_BUTTON_CROSS_RIGHT     =9,
//    AXES_BUTTON_CROSS_DOWN      =10,    AXES_BUTTON_CROSS_LEFT      =11,
//    AXES_BUTTON_L2     =12,    AXES_BUTTON_R2    =13,
//    AXES_BUTTON_L1     =14,   AXES_BUTTON_R1    =15,
//    AXES_BUTTON_TRIANGLE =16,   AXES_BUTTON_CIRCLE   =17,
//    AXES_BUTTON_CROSS    =18,   AXES_BUTTON_SQUARE   =19
//};

std::vector<int> JoyButtonsArray( 17, 0 );
std::vector<float> JoyAxesArray( 20, 0.0 );
geometry_msgs::Twist turtle_msg;
int last_L2,running,AXES_BUTTON_L2;

inline void joy_ps4_Callback( const sensor_msgs::Joy::ConstPtr &joy_msg );
inline void running_Callback( const std_msgs::Int32::ConstPtr &running_msg);

int main( int argc, char **argv ){
    ros::init( argc, argv, "turtle_circle" );
    ros::NodeHandle nh;

    ros::Subscriber sub_ps4 = nh.subscribe( "joy", 1, joy_ps4_Callback );
    ros::Subscriber sub_running = nh.subscribe( "running", 1, running_Callback);

    ros::Publisher pub_turtle = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

    ros::Rate loop_rate( 1.0f/CYCLE_PERIOD );
    while ( ros::ok()){
        AXES_BUTTON_L2 = JoyButtonsArray[6];
        
        if(last_L2 == 0 && AXES_BUTTON_L2 == 1){
            if(running == 1){
                running = 0;
            }
            else{
                running = 1;
            }
        }

        if(running == 1){
            turtle_msg.linear.x = 1;
            turtle_msg.angular.z = 1;
        }
        else{
            turtle_msg.linear.x = 0;
            turtle_msg.angular.z = 0;
        }

        if(AXES_BUTTON_L2 == 0){
            last_L2 = 0;
        }
        else{
            last_L2 = 1;
        }

        ros::spinOnce();
        loop_rate.sleep();
        pub_turtle.publish(turtle_msg);
    }
    return 0;
}


inline void joy_ps4_Callback( const sensor_msgs::Joy::ConstPtr &joy_msg ){
    JoyButtonsArray = joy_msg->buttons;
    JoyAxesArray = joy_msg->axes;
}

inline void running_Callback( const std_msgs::Int32::ConstPtr &running_msg ){
    running = running_msg->data;
}