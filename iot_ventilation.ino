/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */
#include<L298N.h>
#include <ros.h>
#include <std_msgs/Int32.h>
const unsigned int IN1 = 12;
const unsigned int IN2 = 11;
const unsigned int EN = 10;
ros::NodeHandle  nh;
L298N motor(EN, IN1, IN2);
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

ros::Subscriber<std_msgs::Int32> sub("/ventilation", &messageCb );

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
