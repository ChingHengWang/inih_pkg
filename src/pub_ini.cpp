#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include "../lib/inih/cpp/INIReader.h"
#include <iostream>
using namespace std;
INIReader reader("/home/zach/catkin_ws/src/inih_pkg/test.ini");


int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);
  int count = 0;

  if (reader.ParseError() < 0) {
      std::cout << "Can't load 'test.ini'\n";
     return 1;
  }
  cout << "ini content " << endl;
  cout << "name = "<<reader.Get("my_section","name","UNKNOW")<<endl;
  cout << "number = "<<reader.Get("my_section","number","UNKNOW")<<endl;


  while (!ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
