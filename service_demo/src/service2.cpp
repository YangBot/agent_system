#include<ros/ros.h>
#include<service_demo/Greeting.h>
#include<service_demo/getbot.h>
#include<string.h>

service_demo::getbot msg2;  

bool handle_function( service_demo::Greeting::Request &req , service_demo::Greeting::Response &res){


     ROS_INFO("robot2  in \"ready\" state");   msg2.state="executing";
     ROS_INFO("Request from task %d of %s",req.task,req.name.c_str());
     ROS_INFO("robot2  in \"executing\" state");
      ros::Rate loop_rate(0.3333);
      loop_rate.sleep();
      ROS_INFO("robot2  in \"ready\" state \n");
     res.feedback = "ready"  ;      msg2.state="ready";  //  robot1
     return true;


}




int main (int argc,char **argv){
   ros::init(argc,argv,"node_robot_2");
   ros::NodeHandle nh[2];


   msg2.state="ready";
   ros::Publisher pub=nh[0].advertise<service_demo::getbot>("agent_feedback",1);   //creat publisher

   ros::ServiceServer service = nh[1].advertiseService("agent_task_2",handle_function); 

          
   ros::Rate loop_rate(0.5);
   while(ros::ok()){

      ros::spinOnce();
       pub.publish(msg2);
      loop_rate.sleep();  
   }
   
      

   return 0 ;

}
