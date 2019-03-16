1、ros版本：kinetic，工程编译无误

2、通信机制
该工程一共有3个node : node_mini_factory_server 、 robot_1 、 robot_2
         有一个topic:  /agent_feedback
         有两个server： /task_1  、 /task_2
             
首先 robot1 和 robot2将各自状态发送给 /agent_feedback ，然后node_mini_factory_server 订阅该 topic的消息。
当客户端 node_mini_factory_server 检测到两个机器人都处于空闲状态时，依次向 robot1 、 robot2 发送任务1-5 。


3、显示打印信息
打开四个终端，依次运行：
catkin_make 、roscore
rosrun service_demo service
rosrun service_demo service2
rosrun service_demo client


4、使用launch文件同时启动三个节点
指令：roslaunch service_demo multi_agent_system.launch
启动launch文件后可用rosnode list查看到有三个节点存在、 使用rostopic list查看到有一个topic存在、使用rosservice list看到有两个service存在。
还可以使用rostopic echo /agent_feedback  查看到该topic上传送的消息。
