



roslaunch service_demo multi_agent_system.launch



catkin_make 
roscore
rosrun service_demo service
rosrun service_demo service2
rosrun service_demo client
