#define CTRL_PERIOD 0.02f
#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
int target_x = 10.0;
int target_y = 10.0; //<-使われてないから消してもいいかも
/*****
float judge = 0.0f; //<-使われてないから消してもいいかも
******/
float position_x = 0.0f;
float position_y = 0.0f;
float position_theta = 0.0f;
/***
int iko(int target_x, int position_x); //<-46行目でコメントアウトされてるから、こっちもコメントアウトしておきます
***/
// void iko1(int target_x, int position_x, int a);
void iko1();
geometry_msgs::Twist twist;
/******
void cB_jungkeun(const std_msgs::Float32::ConstPtr &msg_Float); //<-使われていないから消してもいいかも
******/
void cB_turtle_pose(const turtlesim::Pose::ConstPtr &msg_pose);
int main(int argc, char **argv)
{
    ros::init(argc, argv, "kansututle");
    ros::NodeHandle nh;
    ros::Rate loop_rate(1.0 / CTRL_PERIOD);
    ros::Publisher turtle_cmd_vel =nh.advertise<geometry_msgs::Twist> ("turtle1/cmd_vel",1);
    ros::Subscriber turtle_pose = nh.subscribe("turtle1/pose",1,cB_turtle_pose);
    /***
    ros::Subscriber jungkeun = nh.subscribe("start",1,cB_jungkeun); //<-使われていないので消してもいいかも
    ***/
    while(ros::ok())
    {
        // iko1(target_x,position_x,6);  //6ではなく、変数を入れないといけないですが、13行で　int aを したため、固定された定数でしか設定が出来ません。
        iko1();
        ros::spinOnce();
        // twist.linear.x = iko(10,position_x); //<-46行目の関数を使うならこうする
        turtle_cmd_vel.publish(twist);
        loop_rate.sleep();
    ROS_INFO("%s,%f,%s,%f,%s,%f,\n","x->",position_x,"y->",position_y,"theta->",position_theta);
    }
   return 0;
}
// int iko(int target_x, int position_x) //<-この関数もよくできていると思います。target_xとposition_xは6行目11行目で宣言されているので、名前を変えた方が良いと思います。（同じ名前があると難しいので）
// {                                     //   全てint型で宣言されているので思ったように動かないかもしれないです。
//     int a;
//     a = target_x - position_x;
//     return a;
// }
// void iko1(int target_x, int position_x, int a)

void iko1()// <-よくできていると思います。
{
    twist.linear.x = target_x - position_x;
 if(twist.linear.x < 0.01)
 {
     twist.linear.x = 0.0;
 }
}
void cB_turtle_pose(const turtlesim::Pose::ConstPtr &msg_pose)
{
     position_x = msg_pose->x;
     position_y = msg_pose->y;
     position_theta = msg_pose->theta;
}
/*********
void cB_jungkeun(const std_msgs::Float32::ConstPtr &msg_Float) //<-使われてないから消してもいいかも
{
        judge = msg_Float->data;      
}
*********/