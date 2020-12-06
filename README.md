# Patient-Monitoring-System
# Hardware
  2 Arduinos with USB Cables, to make Serial Communication. (any of them works. I used 2 Arduino UNOs)
  MAX30102 PulseOximeter
  AD8232 ECG Sensor
  LM35 Temperature Sensor
  L298N Motor Driver
  5V PC Fan and a pipe
  20% Coding, 80% Research
  ![Wiring](https://github.com/oguzalp7/Patient-Monitoring-System/blob/main/Wiring.png)
  And how is Patient Monitoring System looks like:
  ![System](https://github.com/oguzalp7/Patient-Monitoring-System/blob/main/3c656eca-b337-4419-a031-9e91c1f474ba.jpg)


# 1-Installation
  Make every bash script executable : ex. "sudo chmod +x installROS.sh"
  Make sure the bash scripts are located in Home directory.
  After making each script executable then "./installROS.sh" this script should download every dependency so far.
  
# 2-Running the system
  The system should be running when typing "./prototype1.sh" to the terminal.
  
# 3-Node-Red
  Go head and copy "flows.json" and go "localhost:1880" with your favorite web browser.
  From the selection menu; select manage palette and type "dashboard"
  Again from the selection menu; select Import
  Paste the "flows.json" that you've copied before.
  Last step is to click "Deploy" button to create an interface.
  
# Troubleshooting
  If any problem occurs there are some list of references to solve issues:
  https://flows.nodered.org/node/node-red-contrib-ros
  https://flows.nodered.org/node/node-red-dashboard
  http://wiki.ros.org/melodic/Installation/Ubuntu
  For further questions feel free to contact me: osaglam1@binghamton.edu
  Add me in LinkedIn: https://www.linkedin.com/in/oguzalp-saglam961881/
