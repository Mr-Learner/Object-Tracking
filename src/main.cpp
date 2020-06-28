#include "yolo_test/yolo.hpp"
#include <ros/ros.h>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "yolo_test");
    ros::NodeHandle nh;
    YOLO_Adaption::YOLO_ROS yolo(nh);

    ros::spin();
    return 0;
}