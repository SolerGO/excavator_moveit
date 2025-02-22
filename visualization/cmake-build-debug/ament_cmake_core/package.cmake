set(_AMENT_PACKAGE_NAME "excavator_ros_visualization")
set(excavator_ros_visualization_VERSION "2.12.1")
set(excavator_ros_visualization_MAINTAINER "SolerGO <solergaming555@gmail.com>")
set(excavator_ros_visualization_BUILD_DEPENDS "class_loader" "eigen" "libqt5-opengl-dev" "qtbase5-dev" "moveit_common" "geometric_shapes" "interactive_markers" "moveit_ros_robot_interaction" "moveit_ros_planning_interface" "moveit_ros_warehouse" "object_recognition_msgs" "pluginlib" "rclcpp" "rclpy" "rviz2" "tf2_eigen")
set(excavator_ros_visualization_BUILD_DEPENDS_pluginlib_VERSION_GTE "1.11.2")
set(excavator_ros_visualization_BUILDTOOL_DEPENDS "ament_cmake" "pkg-config")
set(excavator_ros_visualization_BUILD_EXPORT_DEPENDS "moveit_common" "geometric_shapes" "interactive_markers" "moveit_ros_robot_interaction" "moveit_ros_planning_interface" "moveit_ros_warehouse" "object_recognition_msgs" "pluginlib" "rclcpp" "rclpy" "rviz2" "tf2_eigen")
set(excavator_ros_visualization_BUILD_EXPORT_DEPENDS_pluginlib_VERSION_GTE "1.11.2")
set(excavator_ros_visualization_BUILDTOOL_EXPORT_DEPENDS )
set(excavator_ros_visualization_EXEC_DEPENDS "moveit_common" "geometric_shapes" "interactive_markers" "moveit_ros_robot_interaction" "moveit_ros_planning_interface" "moveit_ros_warehouse" "object_recognition_msgs" "pluginlib" "rclcpp" "rclpy" "rviz2" "tf2_eigen")
set(excavator_ros_visualization_EXEC_DEPENDS_pluginlib_VERSION_GTE "1.11.2")
set(excavator_ros_visualization_TEST_DEPENDS )
set(excavator_ros_visualization_GROUP_DEPENDS )
set(excavator_ros_visualization_MEMBER_OF_GROUPS )
set(excavator_ros_visualization_DEPRECATED "")
set(excavator_ros_visualization_EXPORT_TAGS)
list(APPEND excavator_ros_visualization_EXPORT_TAGS "<build_type>ament_cmake</build_type>")
list(APPEND excavator_ros_visualization_EXPORT_TAGS "<rviz plugin=\"robot_state_rviz_plugin_description.xml\"/>")
list(APPEND excavator_ros_visualization_EXPORT_TAGS "<rviz plugin=\"planning_scene_rviz_plugin_description.xml\"/>")
list(APPEND excavator_ros_visualization_EXPORT_TAGS "<rviz plugin=\"motion_planning_rviz_plugin_description.xml\"/>")
list(APPEND excavator_ros_visualization_EXPORT_TAGS "<rviz plugin=\"trajectory_rviz_plugin_description.xml\"/>")
