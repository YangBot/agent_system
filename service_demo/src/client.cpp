#include<ros/ros.h>
#include<service_demo/Greeting.h>
#include<service_demo/getbot.h>
#include<string.h>

int flag1=2,flag2=2;;    
int i=1;
void getbotCallback(const service_demo::getbot::ConstPtr &msg)    //sub  robot1
{
    
      if( msg->state=="ready")
       flag1=1 ;
      else
       flag1=2;
      ROS_INFO("From topic: robot1 in \" %s \" state",msg->state.c_str());

   

}

void getbotCallback2(const service_demo::getbot::ConstPtr &msg2)   //sub robot2
{
    
      if( msg2->state=="ready")
       flag2=1 ;
      else
       flag2=2;
  
      ROS_INFO("From topic: robot2 in \" %s \" state\n",msg2->state.c_str());
   

}





int main(int argc,char **argv){

    ros::init(argc,argv,"node_mini_factory_server");
    ros::NodeHandle nh[2],n[2];

    ros::ServiceClient client1 = nh[0].serviceClient<service_demo::Greeting>("agent_task_1");
    ros::ServiceClient client2 = nh[1].serviceClient<service_demo::Greeting>("agent_task_2");

    service_demo::Greeting srv[2];
    srv[0].request.name = "robot1";
    srv[1].request.name = "robot2";

   ros::Subscriber sub= n[0].subscribe("agent_feedback",1,getbotCallback);     //sub topic
   ros::Subscriber sub2= n[1].subscribe("agent_feedback",1,getbotCallback2);     //sub topic
    

while(ros::ok)
{

 ros::spinOnce();
 
if(i<=5)   {

if( flag1==1 && flag2==1 )
{


    srv[0].request.task = i;  srv[1].request.task =i;  


    ROS_INFO("Post task %d to the robot_1 ",i);
    if(client1.call(srv[0])){
       ROS_INFO("Feedback from server :robot1 is in \" %s \" state. ",srv[0].response.feedback.c_str());

     }
    else{
       ROS_ERROR("Failed to call service robot_1");
       return 1;
     }



    ROS_INFO("Post task %d to the robot_2",i);
    if(client2.call(srv[1])){
       ROS_INFO("Feedback from server :robot2 is in \" %s \" state.  \n ",srv[1].response.feedback.c_str());

     }
    else{
       ROS_ERROR("Failed to call service robot_2");
       return 1;
     }

          i++;
       }
    }
    }

     return 0;



}