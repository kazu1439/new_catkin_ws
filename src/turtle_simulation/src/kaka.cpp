#define CTRL_PERIOD 0.02f
#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
int target_x = 10.0;
int target_y = 10.0;
int target_z = 1.0;
int target_a = 5.5;
int target_b = 5.5;

float judge = 0.0f;
float position_x = 0.0f;
float position_y = 0.0f;
float position_theta = 0.0f;
geometry_msgs::Twist twist;
void cB_jungkeun(const std_msgs::Float32::ConstPtr &msg_Float);
void cB_turtle_pose(const turtlesim::Pose::ConstPtr &msg_pose);
int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle4");
    ros::NodeHandle nh;
    ros::Rate loop_rate(1.0 / CTRL_PERIOD);
    ros::Publisher turtle_cmd_vel =nh.advertise<geometry_msgs::Twist> ("turtle1/cmd_vel",1);
    ros::Subscriber turtle_pose = nh.subscribe("turtle1/pose",1,cB_turtle_pose);
       ros::Subscriber jungkeun = nh.subscribe("start",1,cB_jungkeun);
    while(ros::ok())
    {
    ros::spinOnce();
    if(judge)
    {
    twist.linear.x = target_x-position_x;
    if(twist.linear.x < 0.01) // <만 가능 <<두개 하는건 안됨
        {
            twist.linear.x = 0.0;
        }
    if(twist.linear.x == 0.0) //0.0일때 해줬으면 좋겠어 -> == 임
    {
       twist.angular.z = 1.57 - position_theta;
    }
    if(position_theta > 1.5699 )
    {
        twist.angular.z = 0.0;
    }
    if(twist.angular.z == 0.0) //옆으로 돌아갔으니까 거북이 대가리방향이 x임
    {
        twist.linear.x = target_y-position_y;
    }
    if(twist.linear.x < 0.01)
    {
        twist.linear.x = 0.0;
    }
    //여기부터 내가
    if(position_y > 9.95)
    {
        twist.angular.z = -1.57 - position_theta ; //왜 이게 딱 p제어 된거지???
    }
    if(position_theta < -1.569)
    {
        twist.angular.z = 0.0;
         twist.linear.x = position_y - target_z;
    }
    if(position_y == 1.0)
    {
        twist.angular.z = -3.14 - position_theta;
    }
    if(position_theta < -3.13)
    {
        // twist.angular.z = 0;
        twist.linear.x = position_x - target_a ; //왜 5.5로 했는데 안와! target_aは5.5
    }
    if(position_x == 5.5)
    {
        twist.angular.z = -1.57 - position_theta;
    }
        turtle_cmd_vel.publish(twist);
        loop_rate.sleep();
    }
    ROS_INFO("%s,%f,%s,%f,%s,%f,\n","x->",position_x,"y->",position_y,"theta->",position_theta);
    }
    return 0;
}
// 트위스트 앵글러도 바꿔야함
void cB_turtle_pose(const turtlesim::Pose::ConstPtr &msg_pose)
{
     position_x = msg_pose->x;
     position_y = msg_pose->y;
     position_theta = msg_pose->theta;
}
void cB_jungkeun(const std_msgs::Float32::ConstPtr &msg_Float)
{
        judge = msg_Float->data;      
}