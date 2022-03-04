#include "ros/ros.h"
#include "beginner_tutorials/lpf.h"
#include "beginner_tutorials/differential.h"
#include <std_msgs/Int32.h>

#define CTRL_PERIOD 0.02f

int num;
int year;
int month;
int day;
int a,b,c,d,e,f,g,h;
bool input_num = false;

inline void Number_Callback(const std_msgs::Int32::ConstPtr &int_msg);
inline void birthday();

int main(int argc, char **argv){
    
    ros::init( argc, argv, "birthday" );
    ros::NodeHandle nh;

    ros::Subscriber sub_start = nh.subscribe<std_msgs::Int32>( "birthday", 1, Number_Callback );
    
    ros::Rate loop_rate( 1.0f/CTRL_PERIOD );
    while ( ros::ok() ){
        if(input_num){
            if(9999999 < num && num < 100000000){
                year = num/10000;
                month = (num-year*10000)/100;
                day = num - year*10000 - month*100;
                if(month > 12 || day > 31){
                    ROS_INFO("Sorry, I can't find your birthday.");
                    break;
                }
                //ROS_INFO("year:[%d]month:[%d]day:[%d]",year,month,day);
                birthday();
                if(h == 1){
                    ROS_INFO("Your birthday is Sunday.");
                }
                else if(h == 2){
                    ROS_INFO("Your birthday is Monday.");
                }
                else if(h == 3){
                    ROS_INFO("Your birthday is Tuesday.");
                }
                else if(h == 4){
                    ROS_INFO("Your birthday is Wednesday.");
                }
                else if(h == 5){
                    ROS_INFO("Your birthday is Thursday.");
                }
                else if(h == 6){
                    ROS_INFO("Your birthday is Friday.");
                }
                else if(h == 0){
                    ROS_INFO("Your birthday is Saturday.");
                }
                else{
                    ROS_INFO("Sorry, I can't find your birthday.");
                }
            }
            else{
                //ROS_INFO("%d",num);
                ROS_INFO("Sorry, I can't find your birthday.");
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

inline void birthday(){
    if(month == 1|| month == 2){
        year = year - 1;
        month = month + 12;
    }    
    a = (year)/100;
    a = year-a*100;
    b = a/4;
    c = 26*(month + 1)/10;
    d = year/100;
    d = d*-2;
    e = year/400;
    f = a + b + c + d + e + day;
    g = f/7;
    h = f - g*7;
}