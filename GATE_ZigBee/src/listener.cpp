#include "ros/ros.h"
#include "PALGATE_msgs/ZigbeeFrame.h"


/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.

Data structure

>root@rosserv:~$ rosmsg show ZigbeeFrame

[PALGATE_msgs/ZigbeeFrame]:
uint32 seq		// Frame ID
time stamp		// TimeStampt
string capid		// sensor ID
string caplocation	// Sensor location ID
string sensvals		// Sensors values:  Var01#1#Var8#23 
*/



std::string node_name = "ROSServ_ZigData_SUB";

void chatterCallback(const PALGATE_msgs::ZigbeeFrame::ConstPtr& msg)
{
 // ROS_INFO("I heard: [Stamp: %d.%d, Seq: %d , data: %s]",msg->stamp.sec,msg->stamp.nsec,msg->seq,msg->frame_id.c_str());
 ros::Time inst_T = ros::Time::now();
printf("stamp %d.%d",msg->stamp.sec, msg->stamp.nsec);
 ROS_INFO("Delai %dsec %dns, DATA= id %s | loc %s | vals %s",inst_T.sec-msg->stamp.sec, inst_T.nsec-msg->stamp.nsec, msg->capid.c_str(), msg->caplocation.c_str(), msg->sensvals.c_str());
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */

  int z;
  char hostname[32];
  z = gethostname(hostname, sizeof hostname);

  std::stringstream subNode;
  subNode << node_name << "_" << hostname;
  ros::init(argc, argv, subNode.str()); //ros::init(argc, argv,"NodeName"); inisialisation of node name


  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */

  ros::Subscriber sub = n.subscribe(argv[1], 1000, chatterCallback); //argv[1] = Topic Name : type on console [rostopic list -v] to show the list of published topics   


  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}
