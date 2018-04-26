#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/Quaternion.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include <cmath>
#include <tf/transform_datatypes.h>
#include <time.h>

class decision {
private:

    ros::NodeHandle n;

    // communication with person_detector or person_tracker
    ros::Publisher pub_goal_reached;
    ros::Subscriber sub_goal_to_reach;
    ros::Subscriber robot_position;
    // communication with rotation_action
    ros::Publisher pub_rotation_to_do;
    ros::Subscriber sub_rotation_done;
    ros::Subscriber obstacle_signal;
    // communication with translation_action
    ros::Publisher pub_translation_to_do;
    ros::Subscriber sub_translation_done;

    bool cond_rotation;//boolean to check if there is a /rotation_to_do
    bool cond_translation;//boolean to check if there is a /translation_to_do
    bool new_amcl;

    float rotation_to_do;
    float rotation_done;
    float translation_to_do;
    float old_translation_to_do;
    float translation_done;
    float current_orientation;

    bool new_goal_to_reach;//to check if a new /goal_to_reach is available or not
    bool new_rotation_done;//to check if a new /rotation_done is available or not
    bool new_translation_done;//to check if a new /translation_done is available or not

    geometry_msgs::Point goal_to_reach;
    geometry_msgs::Point goal_reached;

    geometry_msgs::Point current_position;
    geometry_msgs::Point old_goal;
    geometry_msgs::Point goals_to_reach[4];
    int current_index;

public:

decision() {

    // communication with moving_persons_detector or person_tracker
    pub_goal_reached = n.advertise<geometry_msgs::Point>("goal_reached", 1);
    //sub_goal_to_reach = n.subscribe("goal_to_reach", 1, &decision::goal_to_reachCallback, this);
    robot_position = n.subscribe("amcl_pose", 1, &decision::robotPositionCallback, this);
    obstacle_signal = n.subscribe("obstacle", 1, &decision::renewAmcl, this);
    //robot_position = n.subscribe("odom", 1, &decision::robotPositionCallback, this);
    // communication with rotation_action
    pub_rotation_to_do = n.advertise<std_msgs::Float32>("rotation_to_do", 0);
    sub_rotation_done = n.subscribe("rotation_done", 1, &decision::rotation_doneCallback, this);
    cond_rotation = false;
    old_translation_to_do =0.;



    // communication with translation_action
    pub_translation_to_do = n.advertise<std_msgs::Float32>("translation_to_do", 0);
    sub_translation_done = n.subscribe("translation_done", 1, &decision::translation_doneCallback, this);
    cond_translation = false;
    current_index = 0;

    initialise_goals();

    new_goal_to_reach = false;
    new_rotation_done = false;
    new_translation_done = false;
    //new_amcl =true;
    //INFINTE LOOP TO COLLECT LASER DATA AND PROCESS THEM
    ros::Rate r(10);// this node will work at 10hz
    while (ros::ok()) {
        ros::spinOnce();//each callback is called once
        update();
        r.sleep();//we wait if the processing (ie, callback+update) has taken less than 0.1s (ie, 10 hz)
    }

}





// void initialise_goals(){

//     goals_to_reach[0].x = 10.9;//22.8;
//     goals_to_reach[0].y = 3.24;//-8.22;
//     goals_to_reach[1].x = 11.7;
//     goals_to_reach[1].y = 2;
//     goals_to_reach[2].x = 14.1;
//     goals_to_reach[2].y = -6.9;
//     goals_to_reach[3].x = 12.4;
//     goals_to_reach[3].y = -6.8;
//     goal_to_reach = goals_to_reach[current_index];
//     //new_amcl = true;
// }

// void initialise_goals(){

//     goals_to_reach[0].x = 9.4;//22.8;
//     goals_to_reach[0].y = 5.66;//-8.22;
//     goals_to_reach[1].x = 10.3;
//     goals_to_reach[1].y = 6.09;
//     goals_to_reach[2].x = 13.9;
//     goals_to_reach[2].y = -6.67;
//     goals_to_reach[3].x = 12.9;
//     goals_to_reach[3].y = -7.09;
//     goal_to_reach = goals_to_reach[current_index];
//     new_amcl = true;
// }


void initialise_goals(){

    goals_to_reach[0].x = 16.4;//22.8;
    goals_to_reach[0].y = -18.6;//-8.22;
    goals_to_reach[1].x = 14;
    goals_to_reach[1].y = -8.29;
    goals_to_reach[2].x = 22.8;
    goals_to_reach[2].y = -5.76;
    goals_to_reach[3].x = 14;
    goals_to_reach[3].y = -8.29;
    goal_to_reach = goals_to_reach[current_index];
    //new_amcl = true;
}





// void boolean shouldPublish(geometry_msgs::Point nxt){

//     if(distancePoints(nxt, old_goal) > 0.1){
//         return true;
//     }
//     else{
//         return false;
//     }

// }


// bool correct_goal(){

//     if 

// }

//UPDATE: main processing
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void update() {
    goal_to_reach = goals_to_reach[current_index];
    // we receive a new /goal_to_reach and robair is not doing a translation or a rotation
    if ( ( new_amcl ) && ( !cond_translation ) && ( !cond_rotation ) ) {
    //if (  new_amcl  ) {

        ROS_INFO("(decision_node) /goal_to_reach received: (%f, %f)", goal_to_reach.x, goal_to_reach.y);

        
        // we have a rotation and a translation to perform
        // we compute the /translation_to_do
        ROS_INFO("(decision_node) /current_position: (%f, %f)", current_position.x, current_position.y);
        translation_to_do =  sqrt(pow(( goal_to_reach.x - current_position.x ),2) + pow(( goal_to_reach.y - current_position.y ),2));
        //translation_to_do = sqrt((goal_to_reach.x*goal_to_reach.x)+(goal_to_reach.y*goal_to_reach.y));
        // if(abs(translation_to_do - old_translation_to_do) < 0.2){
        //     return;
        // }

        goal_to_reach.x -= current_position.x;
        goal_to_reach.y -= current_position.y;

        //old_translation_to_do = translation_to_do;

        ROS_INFO("(decision_node) /translation: (%f)", translation_to_do);
        if ( translation_to_do ) {
            cond_translation = true;

            //we compute the /rotation_to_do
            cond_rotation = true;
            //rotation_to_do = acos((goal_to_reach.x-current_position.x)/ translation_to_do);
            rotation_to_do = acos(goal_to_reach.x/translation_to_do);

            if ( goal_to_reach.y < 0 ){
                rotation_to_do *=-1;

            }
            //rotation_to_do = acos((goal_to_reach.x)/ translation_to_do);
            //rotation_to_do = acos( translation_to_do/(goal_to_reach.x -current_position.x));
            //rotation_to_do = rotation_to_do + current_orientation;
            //rotation_to_do = acos((current_position.x -goal_to_reach.x)/ translation_to_do);
            //rotation_to_do = acos(goal_to_reach.x/translation_to_do);
            ROS_INFO("(decision_node) /rotation_to_do: (%f)", rotation_to_do);
            ROS_INFO("(decision_node) /current_orientation: (%f)", current_orientation);

            rotation_to_do = rotation_to_do - current_orientation;

            //current_orientation = fabs(current_orientation);
            //rotation_to_do = fabs(rotation_to_do);
            // if(current_orientation > rotation_to_do){
            //     rotation_to_do = current_orientation - rotation_to_do;
            // }
        
            // else {
            //     rotation_to_do = rotation_to_do -current_orientation;
            // }
            

            //rotation_to_do = current_orientation - rotation_to_do


            //we first perform the /rotation_to_do
            ROS_INFO("(decision_node) /rotation_to_do: %f", rotation_to_do*180/M_PI);
            std_msgs::Float32 msg_rotation_to_do;
            //to complete
            msg_rotation_to_do.data= rotation_to_do;

            // if(abs(translation_to_do - old_translation_to_do) > 0.1){
            //     pub_rotation_to_do.publish(msg_rotation_to_do);
            // }

            pub_rotation_to_do.publish(msg_rotation_to_do);
            


            ROS_INFO("(decision_node) published");

            //ros::Duration(0.5).sleep();


        }
        else {
            geometry_msgs::Point msg_goal_reached;
            msg_goal_reached.x = 0;
            msg_goal_reached.y = 0;

            ROS_INFO("(decision_node) /rotation goal_reached (%f, %f)", msg_goal_reached.x, msg_goal_reached.y);
            pub_goal_reached.publish(msg_goal_reached);
        }

    }

    //new_goal_to_reach = false;
    new_amcl = false;

    //we receive an ack from rotation_action_node. So, we perform the /translation_to_do
    if ( new_rotation_done ) {
        ROS_INFO("(decision_node) /rotation_done : %f", rotation_done*180/M_PI);
        cond_rotation = false;
        new_rotation_done = false;

        //the rotation_to_do is done so we perform the translation_to_do
        ROS_INFO("(decision_node) /translation_to_do: %f", translation_to_do);
        std_msgs::Float32 msg_translation_to_do;
        //to complete
        msg_translation_to_do.data = translation_to_do;
        // if(abs(translation_to_do - old_translation_to_do) > 0.1){
        //     pub_translation_to_do.publish(msg_translation_to_do);
        // }

        pub_translation_to_do.publish(msg_translation_to_do);
        new_amcl = true;
        
    }

    //we receive an ack from translation_action_node. So, we send an ack to the moving_persons_detector_node
    if ( new_translation_done ) {
        ROS_INFO("(decision_node) /translation_done : %f\n", translation_done);
        cond_translation = false;
        new_translation_done = false;

        //the translation_to_do is done so we send the goal_reached to the detector/tracker node
        geometry_msgs::Point msg_goal_reached;
        ROS_INFO("(decision_node) /translation goal_reached (%f, %f)", msg_goal_reached.x, msg_goal_reached.y);
        //to complete
        //msg_goal_reached.data = translation_done;
        pub_goal_reached.publish(msg_goal_reached);

        ROS_INFO(" ");
        ROS_INFO("(decision_node) waiting for a /goal_to_reach");

        current_index = (current_index + 1) % 3;
        ROS_INFO("(decision_node) incremented goal_to_reach index %d", current_index);
        new_amcl = true;
        ROS_INFO("(decision_node) new amcl ");
        //translation_to_do =  sqrt(pow(( goal_to_reach.x - current_position.x ),2) + pow(( goal_to_reach.y - current_position.y ),2));
        //rotation_to_do = acos((goal_to_reach.x -current_position.x)/ translation_to_do);

        //std_msgs::Float32 msg_rotation_to_do;
            //to complete
        //msg_rotation_to_do.data= rotation_to_do;

        //pub_rotation_to_do.publish(msg_rotation_to_do);


    }

    //new_amcl = false;

}// update

//CALLBACKS
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void goal_to_reachCallback(const geometry_msgs::Point::ConstPtr& g) {
// process the goal received from moving_persons detector
    ROS_INFO("(decision_node) goal_reached");
    new_goal_to_reach = true;
    goal_to_reach.x = g->x;
    goal_to_reach.y = g->y;

}

void rotation_doneCallback(const std_msgs::Float32::ConstPtr& a) {
// process the angle received from the rotation node
    ROS_INFO("(decision_node) rotationDone");
    new_rotation_done = true;
    rotation_done = a->data;

}


void renewAmcl(const std_msgs::Float32::ConstPtr& a) {
// process the angle received from the rotation node
    ROS_INFO("(decision_node) obstacle");
    new_amcl = true;
    //new_rotation_done = true;
    //rotation_done = a->data;
}

void robotPositionCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& o) {
//void robotPositionCallback(const nav_msgs::Odometry::ConstPtr& o) {
    ROS_INFO("(decision_node) received amcl");
    //new_amcl = true;
    current_position.x = o->pose.pose.position.x;
    current_position.y = o->pose.pose.position.y;
    current_position.z = o->pose.pose.position.z;

    current_orientation = tf::getYaw(o->pose.pose.orientation);


}

void translation_doneCallback(const std_msgs::Float32::ConstPtr& r) {
// process the range received from the translation node
    ROS_INFO("(rotation_action_node) translation_to_do");
    new_translation_done = true;
    translation_done = r->data;

}

// Distance between two points
float distancePoints(geometry_msgs::Point pa, geometry_msgs::Point pb) {

    return sqrt(pow((pa.x-pb.x),2.0) + pow((pa.y-pb.y),2.0));

}

};

int main(int argc, char **argv){

    ROS_INFO("(decision_node) waiting for a /goal_to_reach");
    ros::init(argc, argv, "decision");

    decision bsObject;

    ros::spin();

    return 0;
}
