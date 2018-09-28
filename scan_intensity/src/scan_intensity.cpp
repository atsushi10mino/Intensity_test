#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"


ros::Publisher intensity_point_pub;
sensor_msgs::LaserScan strong;//,adjust;
/*
void intensity_adjustment(float range)
{
	float adjust = range;//hakattekimero
}*/
void intensityCallback(const sensor_msgs::LaserScan &msg)
{
	
	//int count = 0;
	//int j = 0;
	
	strong = msg;
	for(int aho = 0 ; aho < strong.ranges.size() ; aho++)
	{
		strong.ranges[aho] = 0;
		strong.intensities[aho] = 0;
	}

	//strong.ranges.clear();
	//strong.intensities.clear();
	
/*	adjust = msg;
	for(int gensui = 0 ; gensui < adjust.ranges.size() ; gensui++ )
	{
		if(adjust.intensities[gensui] > 6000 && adjust.ranges[gensui] > 1)
			adjust.intensities[gensui] *= 1.5;  
	}*/
	
	float max_intensity = *std::max_element(msg.intensities.begin(),msg.intensities.end());
	float min_intensity = *std::min_element(msg.intensities.begin(),msg.intensities.end());

	for(int i = 0 ; i < strong.ranges.size() ;  i++)
	{		
		if(max_intensity > 10000 && (msg.intensities[i] - min_intensity) / (max_intensity - min_intensity) > 0.65)
		{	
			strong.ranges.insert(strong.ranges.begin() + i, msg.ranges[i]);
			strong.intensities.insert(strong.intensities.begin() + i, msg.intensities[i]);

			//j++;	
			/*ROS_INFO("number:%d,intensities:%f",i,msg.intensities[i]);
			ROS_INFO("number:%d,ranges:%f",i,msg.ranges[i]);
			if(msg.intensities[i] == 0 && msg.ranges[i] <= 0.011)
				count++;*/
		}
	
	}
	intensity_point_pub.publish(strong); 
	//ROS_INFO("hogehoge,%d",count);
}

int main(int argc, char **argv)
{
	ros::init(argc,argv,"scan_intensity");
	ros::NodeHandle nh;
	
	ros::Subscriber intensity_sub = nh.subscribe("scan",100,intensityCallback);
	
	intensity_point_pub = nh.advertise<sensor_msgs::LaserScan>("strong_reflection_point",100);
	
	ros::spin();

	return 0;
}
