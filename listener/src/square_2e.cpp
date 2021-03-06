#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <math.h>


float X; 
float a;
float N;
void joint4angleCallback(const std_msgs::Float64 msg)
{
    X = msg.data;
    ROS_INFO("X: %f", X); 
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "rotate");
  
  ros::NodeHandle n;

  ros::Publisher pub3 = n.advertise<std_msgs::Float64>("/robot/joint5_position_controller/command", 100);

  ros::Subscriber sub3 = n.subscribe("/robot/joint5_position_controller/command", 1000, joint4angleCallback);
  
  ros::Rate loop_rate(10); // 10 per 1 sec

  ros::Time startTime = ros::Time::now(); 
 
  a = 0; 
  while (ros::ok())
  {   
	  X = sin(a); 
      std_msgs::Float64 msg_to_send; 
      if (X > 0) 
      { 
		  N = 1; 
	  } else 
	  { 
		   N = 0;
	  }
         msg_to_send.data = N;    
         pub3.publish(msg_to_send);
         ROS_INFO("Moving endeffector 2: %f", msg_to_send); 
         
         a = a + 0.1; 
    ros::spinOnce();
   
    loop_rate.sleep();
  }

  return 0;
}
