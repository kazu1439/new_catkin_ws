#include "ros/ros.h"
#define CTRL_PERIOD 0.02f


int tasu(int a, int b);

int hiku(int something, int anything);

int kakeru(int someone, int anyone);

float waru(float somewhere, float anywhere);

void keisan(int num1, int num2);



int main(int argc, char **argv){
    
    ros::init( argc, argv, "kansu" );
    ros::NodeHandle nh;
    ros::Rate loop_rate( 1.0f/CTRL_PERIOD );
    while ( ros::ok() ){
        
        //tasu()
        int ans = tasu(1,2);
        // int ans;
        // ans = tasu(1,2);
        ROS_INFO("tasu->%d\n",ans);
        
        //hiku()
        ROS_INFO("hiku->%d\n",hiku(9,3));
        
        //kakeru() & waru()
        ROS_INFO("kakeru & waru->%f\n",waru(12,kakeru(2,3)));

        keisan(6,9);

        ros::spinOnce();
        loop_rate.sleep();
    }
}

int tasu(int a, int b){//足し算
    int c;
    c = a + b;
    return c;
}

int hiku(int something, int anything){//引き算
    return something - anything;
}

int kakeru(int someone, int anyone){//かけ算
    int they = someone * anyone;
    return they;
}

float waru(float somewhere, float anywhere){//割り算
    float house = somewhere / anywhere;
    return house;
}

void keisan(int num1, int num2){//全部
    ROS_INFO("%d",tasu(num1,num2));
    ROS_INFO("%d",hiku(num1,num2));
    ROS_INFO("%d",kakeru(num1,num2));
    ROS_INFO("%f\n",waru(num1,num2));
    //return ない
}

