#ifndef YOLO_H
#define YOLO_H


#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/BoundingBox.h>
#include <ros/ros.h>
#include <std_msgs/Int16.h>
namespace YOLO_Adaption
{
    class YOLO_ROS
    {
    public:
        explicit YOLO_ROS(ros::NodeHandle &nodehandle);
        void init();
        void Callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr &img);
        int calculateCenter(const int &min, const int &max);
        void movecamera();
    private:
        ros::NodeHandle nodehandle;
        ros::Publisher motor_pub;
        std_msgs::Int16 motor_topic;
        int x_center;
        int y_center;
    };
}
#endif