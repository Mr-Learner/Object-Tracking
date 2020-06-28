#include "yolo_test/yolo.hpp"

namespace YOLO_Adaption{

    YOLO_ROS::YOLO_ROS(ros::NodeHandle &nh) : nodehandle(nh) {
        ROS_INFO("start");
        init();
    }
    
    void YOLO_ROS::init(){
        motor_pub = nodehandle.advertise<std_msgs::Int16>("motor_speed", 100);
        
        ros::Subscriber msg_sub = nodehandle.subscribe("/darknet_ros/bounding_boxes",300,&YOLO_ROS::Callback, this);
        ros::spin();
    }

    void YOLO_ROS::Callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr &boxes)
    {
        darknet_ros_msgs::BoundingBox Person_info;
        for (auto i : boxes->bounding_boxes)
        {
            //ROS_INFO("------------------");
            //ROS_INFO("Name : %s",i.Class.c_str());
            //ROS_INFO("probability : %f",(float)i.probability);
            //ROS_INFO("x_min : %d",(int)i.xmin);
            //ROS_INFO("x_max : %d",(int)i.xmax);
            //ROS_INFO("y_min : %d",(int)i.ymin);
            //ROS_INFO("y_max : %d",(int)i.ymax);
            //ROS_INFO("------------------");
            if (i.Class == "person")
            {
                    if ((float)i.probability >= (float)Person_info.probability)
                    {
                        
                        Person_info.Class = i.Class.c_str();
                        Person_info.probability = (float)i.probability;
                        Person_info.xmin = (int)i.xmin;
                        Person_info.xmax = (int)i.xmax;
                        Person_info.ymin = (int)i.ymin;
                        Person_info.ymax = (int)i.ymax;
                    }
            }
        }
        if (Person_info.Class == "person")
        {
        x_center = calculateCenter(Person_info.xmin, Person_info.xmax);
        y_center = calculateCenter(Person_info.ymin, Person_info.ymax);
        }
        else
        {
            x_center = 320;
            y_center = 240;
        }
        
        movecamera();
    }

    int YOLO_ROS::calculateCenter(const int &min, const int &max)
    {
        return (min+max)/2;
    }

    void YOLO_ROS::movecamera()
    {
        int x,y;
        x = (x_center / 128);
        
        
        switch ((y_center-240) / 96)
        {
        case -2:
            y = 2;
            break;
        case -1:
            y= 1;
            break;
        case 0:
            y = 0;
            break;
        case 1:
            y = -1;
            break;
        case 2:
            y = -2;
            break;
        default:
            break;
        }
        ROS_INFO("x = %d, y = %d",x,y);
        motor_topic.data = x;
        motor_pub.publish(motor_topic);
    }

}