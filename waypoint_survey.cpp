#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> generateWaypoints(int width, int height, int stepSizeY, int stepSizeX, int startY, int startX, bool fromCenter) {
    vector<pair<int, int>> waypoints;
    int forward = stepSizeX;
    int upward = stepSizeY;

    if (fromCenter) {
        startX -= width / 2;
        startY -= height / 2;
    }
    int x = startX;
    int y = startY;

    while (y <= startY + height) {
        while ((forward > 0 && x <= startX + width) || (forward < 0 && x >= 0)) {
            waypoints.push_back(make_pair(x, y));
            x += forward;
        }
        x -= forward; // One more forward value may have been added in the last step, correction is being made
        y += upward;
        forward = -forward; // reverse the direction
    }
    return waypoints;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "waypoint_publisher_node");
    ros::NodeHandle nh;

    ros::Publisher waypoint_pub = nh.advertise<std_msgs::Header>("waypoints", 10);

    int width = 10;
    int height = 10;
    int stepSizeX = 1;
    int stepSizeY = 1;
    int startY = 2;
    int startX = 2;
    bool fromCenter = true; // Orta noktadan başlamak için true olarak ayarlanır

    vector<pair<int, int>> waypoints = generateWaypoints(width, height, stepSizeY, stepSizeX, startY, startX, fromCenter);

    ros::Rate loop_rate(1); // Publish rate: 1 Hz

    while (ros::ok()) {
        std_msgs::Header msg;
        for (auto point : waypoints) {
            msg.stamp = ros::Time::now();
            msg.frame_id = "map";
            msg.seq++;

            // Set x and y coordinates from the waypoints
            msg.x = point.first;
            msg.y = point.second;

            // Publish the waypoint
            waypoint_pub.publish(msg);

            // Wait for the next iteration
            loop_rate.sleep();
        }
        ros::spinOnce();
    }

    return 0;
}
