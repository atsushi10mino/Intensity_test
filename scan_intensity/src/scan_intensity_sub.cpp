#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

void intensityCallback(const sensor_msgs::LaserScan &msg)
{
	int count = 0;
	for(int i =0 ; i < 720 ;  i++)
	{		
		/*if(msg.intensities[i]>10000)*/
			ROS_INFO("number:%d,intensities:%f",i,msg.intensities[i]);
			ROS_INFO("number:%d,ranges:%f",i,msg.ranges[i]);
			if(msg.intensities[i] == 0 && msg.ranges[i] <= 0.011)
				count++;
			
	}
	ROS_INFO("hogehoge,%d",count);
}

int main(int argc, char **argv)
{
	ros::init(argc,argv,"scan_intensity_sub");
	ros::NodeHandle nh;
	ros::Subscriber intensity_sub = nh.subscribe("scan",100,intensityCallback);
	ros::spin();

	return 0;
}
