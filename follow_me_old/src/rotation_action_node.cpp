#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include <cmath>
#include <tf/transform_datatypes.h>
#include "geometry_msgs/Point.h"

#define rotation_error 0.2//radians

#define kp 0.5
#define ki 0
#define kd 0

class rotation_action {
private:

    ros::NodeHandle n;

    // communication with cmd_vel to send command to the mobile robot
    ros::Publisher pub_cmd_vel;

    // communication with amcletry
    ros::Subscriber sub_amcl;

    // communication with decision
    ros::Publisher pub_rotation_done;
    ros::Subscriber sub_rotation_to_do;

    float rotation_to_do, rotation_done;
    bool cond_rotation;// boolean to check if we still have to rotate or not

    bool new_rotation_to_do;//to check if a new /rotation_to_do is available or not
    bool new_amcl;//to check if  new data from amcletry are available

    float init_orientation;
    float current_orientation;

    float error_integral;
    float error_previous;

public:

rotation_action() {

    // communication with cmd_vel to command the mobile robot
    pub_cmd_vel = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);

    // communication with amcletry
    //sub_amcl = n.subscribe("amcl_now", 1, &rotation_action::amclCallback, this);
    sub_amcl = n.subscribe("odom", 1, &rotation_action::amclCallback, this);
    cond_rotation = false;
    new_rotation_to_do = false;
    new_amcl = false;

    // communication with decision
    pub_rotation_done = n.advertise<std_msgs::Float32>("rotation_done", 1);
    sub_rotation_to_do = n.subscribe("rotation_to_do", 1, &rotation_action::rotation_to_doCallback, this);//this is the rotation that has to be performed

    error_integral = 0;
    error_previous = 0;

    //INFINTE LOOP TO COLLECT LASER DATA AND PROCESS THEM
    ros::Rate r(10);// this node will run at 10hz
    while (ros::ok()) {
        ros::spinOnce();//each callback is called once to collect new data: laser + robot_moving
        update();//processing of data
        r.sleep();//we wait if the processing (ie, callback+update) has taken less than 0.1s (ie, 10 hz)
    }

}

//UPDATE: main processing
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void update() {
    // if(new_amcl == false){
    //     ROS_INFO("(rotation_action_node) new amcl: false");
    // }
    // we receive a new /rotation_to_do
    if ( new_rotation_to_do && new_amcl ) {
        new_rotation_to_do = false;
        ROS_INFO("\n(rotation_action_node) processing the /rotation_to_do received from the decision node");
        ROS_INFO("(rotation_action_node) rotation_to_do: %f", rotation_to_do*180/M_PI);

        init_orientation = current_orientation;
        rotation_done = current_orientation;
        rotation_to_do += current_orientation;
        cond_rotation = true;
        error_previous = rotation_to_do;

        if ( rotation_to_do > M_PI )
            rotation_to_do -= 2*M_PI;
        if ( rotation_to_do < -M_PI )
            rotation_to_do += 2*M_PI;

    }
    //we are performing a rotation
    if ( new_amcl && cond_rotation ) {
        rotation_done = current_orientation;
        float error = ( rotation_to_do - rotation_done );

        if ( error > M_PI ) {
            ROS_WARN("(rotation_action node) error > 180 degrees: %f degrees -> %f degrees", error*180/M_PI, (error-2*M_PI)*180/M_PI);
            error -= 2*M_PI;
        }
        else
            if ( error < -M_PI ) {
                ROS_WARN("(rotation_action node) error < -180 degrees: %f degrees -> %f degrees", error*180/M_PI, (error+2*M_PI)*180/M_PI);
                error += 2*M_PI;
            }

        cond_rotation = ( fabs(error) > rotation_error );

        float rotation_speed = 0;
        if ( cond_rotation ) {
            //TO COMPLETE
            //Implementation of a PID controller for rotation_to_do;
            //rotation_speed = kp*error + ki * error + kp * error_derivation;

            float error_derivation;//To complete
            // error_derivation = fabs(error_previous - error);
            //ROS_INFO("error_derivaion: %f", error_derivation);

            // error_integral += error;//To complete
            //ROS_INFO("error_integral: %f", error_integral);

            //control of rotation with a PID controller
            rotation_speed = kp * error + ki * error_integral + kd * error_derivation;
            ROS_INFO("(rotation_action_node) current_orientation: %f, orientation_to_reach: %f -> rotation_speed: %f", rotation_done*180/M_PI, rotation_to_do*180/M_PI, rotation_speed*180/M_PI);
        }
        else {
            ROS_INFO("(rotation_action_node) current_orientation: %f, orientation_to_reach: %f -> rotation_speed: %f", rotation_done*180/M_PI, rotation_to_do*180/M_PI, rotation_speed*180/M_PI);
            rotation_done -= init_orientation;

            if ( rotation_done > M_PI )
                rotation_done -= 2*M_PI;
            if ( rotation_done < -M_PI )
                rotation_done += 2*M_PI;

            ROS_INFO("(rotation_action_node) final rotation_done: %f", rotation_done*180/M_PI);
            ROS_INFO("(rotation_action_node) waiting for a /rotation_to_do");

            std_msgs::Float32 msg_rotation_done;
            msg_rotation_done.data = rotation_done;
            pub_rotation_done.publish(msg_rotation_done);

        }

        geometry_msgs::Twist twist;
        twist.linear.x = 0;
        twist.linear.y = 0;
        twist.linear.z = 0;

        twist.angular.x = 0;
        twist.angular.y = 0;
        twist.angular.z = rotation_speed;

        pub_cmd_vel.publish(twist);



    }
   new_amcl = false;
        
    
}// update

//CALLBACKS
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
//void amclCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& o) {
void amclCallback(const nav_msgs::Odometry::ConstPtr& o) {
    //ROS_INFO("(rotation_action_node) received amcl");
    new_amcl = true;
    current_orientation = tf::getYaw(o->pose.pose.orientation);

}

void rotation_to_doCallback(const std_msgs::Float32::ConstPtr & a) {
    ROS_INFO("(rotation_action_node) received rotation to do");
    new_rotation_to_do = true;
    rotation_to_do = a->data;   

}

};

int main(int argc, char **argv){

    ros::init(argc, argv, "rotation_action");

    ROS_INFO("(rotation_action_node) waiting for a /rotation_to_do");
    rotation_action bsObject;

    ros::spin();

    return 0;
}
