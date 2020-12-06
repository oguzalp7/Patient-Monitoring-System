/* Author: Oguz Alp Saglam
 * Project: Patient Monitoring System Prototype #1
 * Problems of the prototype:
 * 1-) The sensors are the almost cheapest sensors and they are probably clone.
 * 2-) The sensors must have different frequincies. SPO2 module must be the fastest, then ECG and the slowest should be the temperature sensor
 */
//include libraries and ROS Message Headers
#include<ros.h>
#include<std_msgs/Int32.h>
#include<std_msgs/Float32.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
//Timestamp threshold
#define REPORTING_PERIOD_MS     1000

int temp_pin = A1;  //temperature pin decleration

ros::NodeHandle nh; //creating ROS instance to interface with Computer
PulseOximeter pox;  //creating Oximeter instance from 'MAX30100_PulseOximeter.h'

uint32_t tsLastReport = 0;  //create another timestamp variable

//create ROS Messages instances to provide the communication
//they are really similiar that we've done in the programming assignment.
std_msgs::Float32 temp_msg; 
std_msgs::Int32 ecg_msg;
std_msgs::Int32 spo2_msg;
std_msgs::Int32 bpm_msg;

//ROS Topic Publishers
/*
 * PARAMS: Topic name and the message type(somekind of struct but it has its own protocols)
 * Topic Name: I believe the ROS topics are providing "Socket Programming" based communications.
 * Read the data from microcontroller and send the data to Socket port.
 */
ros::Publisher pub_temp("/temperature", &temp_msg);
ros::Publisher pub_ecg("/ecg_data", &ecg_msg);
ros::Publisher pub_spo2("/spo2_data", &spo2_msg);
ros::Publisher pub_bpm("/bpm_data", &bpm_msg);

//initiliaze the temperature data that I'll use them later
int raw_temp_data;
float temp_voltage, temp_celcius;

void setup() {
  // put your setup code here, to run once:
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
  //pox.setOnBeatDetectedCallback(onBeatDetected);
  nh.initNode();  //ROS Node initialization: So far I believe the ROS Nodes are somekind of set of threads/processes that works parallel.
  // Setting up the Publishers.
  nh.advertise(pub_temp);
  nh.advertise(pub_ecg);
  nh.advertise(pub_spo2);
  nh.advertise(pub_bpm);
}

void loop() {
  // read temperature data and convert to Celcius
  raw_temp_data = analogRead(temp_pin);
  temp_voltage = (raw_temp_data / 1023.0)*5000;
  temp_celcius = temp_voltage/10.0;
  temp_msg.data = temp_celcius; //add to Int32 message type
  pub_temp.publish(&temp_msg); //publish on ROS

  // read ECG data and pusblish on ROS
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    ecg_msg.data = -1; //error state
  }
  ecg_msg.data = analogRead(A0); //read ecg module
  pub_ecg.publish(&ecg_msg);  //publish on ROS

  // This part of the code is referenced from the "MAX30100_PulseOximeter" library.
  // You can find the code in Examples-> MAX30100lib -> MAX30100_Minimal
  pox.update();
  //error handling is made with numbers so that our structure of the system is not being broken.
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        //set the data of the message type
        spo2_msg.data = pox.getHeartRate();
        bpm_msg.data = pox.getSpO2();
        tsLastReport = millis();
  }else{
    //error state, set data = 0
    spo2_msg.data = 0;
    bpm_msg.data = 0;
  }
  //publish on ROS
  pub_spo2.publish(&spo2_msg);
  pub_bpm.publish(&bpm_msg);
  //run the code
  nh.spinOnce();
  delay(500);
}
