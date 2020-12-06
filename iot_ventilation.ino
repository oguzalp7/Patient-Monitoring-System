/*
* Author: Oguz Alp Saglam
* Fake Ventilator
*/
//including libraries and ROS message headers
#include<L298N.h>
#include <ros.h>
#include <std_msgs/Int32.h>

//defining motordriver pins
const unsigned int IN1 = 12;
const unsigned int IN2 = 11;
const unsigned int EN = 10;
ros::NodeHandle  nh;  //creating ROS instance
L298N motor(EN, IN1, IN2); //creating 1 motor instance

//ROS Subscriber Callback
/*
* PARAMS: ROS Int32 type message instance
* The motor driving algorithms runs here
*/
void messageCb( const std_msgs::Int32& toggle_msg){
  while(toggle_msg.data == 1){
    motor.setSpeed(255);
    motor.forward();
    delay(5000);
    //motors.stop();
    motor.backward();
    delay(5000);
  }if(toggle_msg.data == 0){
    motor.stop();
  }
}

// ROS Subscriber instance
ros::Subscriber<std_msgs::Int32> sub("/ventilation", &messageCb );

void setup()
{ 
  nh.initNode(); //ROS Node initialization
  nh.subscribe(sub); //ROS Subscriber
}

void loop()
{  
  //Run the code
  nh.spinOnce();
  delay(1);
}
