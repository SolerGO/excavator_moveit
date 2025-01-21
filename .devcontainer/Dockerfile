FROM osrf/ros:jazzy-desktop-full

# Add user to video group to allow access to webcam
RUN #usermod --append --groups video $USERNAME

# Update all packages
RUN apt update && sudo apt upgrade -y

RUN apt install -y git \
    wget lsb-release gnupg

# Rosdep update
RUN rosdep update

#Install Gazebo Harmonic
RUN curl https://packages.osrfoundation.org/gazebo.gpg --output /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null
RUN apt-get update

#Install ros_qz
RUN apt-get update &&\
    apt install -y \
    ros-jazzy-ros-gz \
    ros-jazzy-moveit \
    ros-jazzy-joint-state-publisher \
    ros-jazzy-joint-state-publisher-gui \
    ros-jazzy-controller-manager \
    ros-jazzy-gripper-controllers \
    ros-jazzy-ros2-control \
    ros-jazzy-ros2-controllers \
    ros-jazzy-gz-ros2-control \
    ros-jazzy-moveit-planners-chomp \
    ros-jazzy-moveit-ros-perception \
    ros-jazzy-moveit-ros-visualization \
    ros-jazzy-moveit-visual-tools



# Source the ROS setup file
RUN echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> ~/.bashrc
