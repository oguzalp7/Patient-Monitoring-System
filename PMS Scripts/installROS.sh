sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt update
sudo apt install ros-melodic-desktop-full
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
sudo apt install python-rosdep
sudo rosdep init
rosdep update
printenv | grep ROS
source /opt/ros/melodic/setup.bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/
catkin_make
source devel/setup.bash
echo $ROS_PACKAGE_PATH
echo "Installation should be completed"
echo "Adding the PMS Files"
sudo apt-get install ros-melodic-rosbridge-server
cd catkin_ws/src
git clone https://github.com/ros-drivers/rosserial.git
git clone https://github.com/OTL/cv_camera.git
catkin_create_pkg PMS std_msgs rospy roscpp
cd PMS
git clone https://github.com/oguzalp7/Patient-Monitoring-System.git
cd 
cd catkin_ws
catkin_make
cd
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install nodejs
node -v
sudo npm install -g --unsafe-perm node-red node-red-admin
sudo ufw allow 1880
node-red-admin install node-red-contrib-ros
