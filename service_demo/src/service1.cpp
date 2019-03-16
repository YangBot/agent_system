#include<ros/ros.h>
#include<service_demo/Greeting.h>
#include<service_demo/getbot.h>
#include<string.h>

service_demo::getbot msg;

bool handle_function( service_demo::Greeting::Request &req , service_demo::Greeting::Response &res){

     ROS_INFO("robot1  in \"ready\" state");     msg.state="executing";

//     msg.state[0]="executing";
     ROS_INFO("Request from task %d of %s",req.task,req.name.c_str());
     ROS_INFO("robot1  in \"executing\" state");

      ros::Rate loop_rate(0.2);
      loop_rate.sleep();
      ROS_INFO("robot1 in \"ready\" state \n");


     res.feedback ="ready";       msg.state="ready";  //  robot1
     return true;

}






int main (int argc,char **argv){
   ros::init(argc,argv,"node_robot_1");
   ros::NodeHandle nh[2];


   msg.state="ready";

   ros::Publisher pub=nh[0].advertise<service_demo::getbot>("agent_feedback",1);   //creat publisher

   ros::ServiceServer service = nh[1].advertiseService("agent_task_1",handle_function); 

          
   ros::Rate loop_rate(0.5);
   while(ros::ok()){
//      ROS_INFO("robot1  in \" %s \"" state",msg.state.c_str());

      ros::spinOnce();
       pub.publish(msg);
      loop_rate.sleep();  
   }


      
      
      

   return 0 ;

}
