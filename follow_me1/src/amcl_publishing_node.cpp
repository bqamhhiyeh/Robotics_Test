
#include "ros/ros.h"
#include "ros/time.h"
#include <cmath>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/Point.h"
#include <tf/transform_datatypes.h>
using namespace std;

class amcl_publishing {

private:
    ros::NodeHandle n;

    ros::Subscriber sub_scan;

    ros::Publisher amcl_pub;
    ros::Subscriber amcl_pos;
    geometry_msgs::PoseWithCovarianceStamped amcl_data;
    bool amcl_recv;
    geometry_msgs::Point current_position;



public:

amcl_publishing() {

    amcl_pos = n.subscribe("amcl_pose", 1, &amcl_publishing::groupCallback, this);

    //pub_amcl_publishing_marker = n.advertise<visualization_msgs::Marker>("moving_persons_detector", 1); // Preparing a topic to publish our results. This will be used by the visualization tool rviz
    amcl_pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("amcl_now", 1);     // Preparing a topic to publish the goal to reach.
    amcl_recv = false;
    //INFINTE LOOP TO COLLECT LASER DATA AND PROCESS THEM
    ros::Rate r(10);// this node will run at 10hz
    while (ros::ok()) {
        ros::spinOnce();//each callback is called once to collect new data: laser + robot_moving
        update();//processing of data
        r.sleep();//we wait if the processing (ie, callback+update) has taken less than 0.1s (ie, 10 hz)
    }

} 

//UPDATE: main processing of laser data and robot_moving
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void update() {

    // we wait for new data of the laser and of the robot_moving_node to perform laser processing
    
    if(amcl_recv){
        publish_amcl();
    }
    

}// update


void publish_amcl(){

    amcl_pub.publish(amcl_data);
    display_current_pose();
}


void display_current_pose(){

    current_position.x = amcl_data.pose.pose.position.x;
    current_position.y = amcl_data.pose.pose.position.y;
    current_position.z = amcl_data.pose.pose.position.z;

    ROS_INFO("(amcl_publishing) /current_position: (%f, %f)", current_position.x, current_position.y);


}

//CALLBACKS
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


void groupCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& data){
    ROS_INFO("(amcl_publishing_node) received amcl");
    amcl_recv = true;
    amcl_data = *data;

}//personsDetectedCallback

};

int main(int argc, char **argv){

    ros::init(argc, argv, "amcl_publishing");

    amcl_publishing bsObject;

    ros::spin();

    return 0;
}
