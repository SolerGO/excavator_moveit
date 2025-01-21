//
// Created by root on 1/20/25.
//
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>

#include <moveit_msgs/msg/display_robot_state.hpp>
#include <moveit_msgs/msg/display_trajectory.hpp>

#include <moveit_msgs/msg/attached_collision_object.hpp>
#include <moveit_msgs/msg/collision_object.hpp>

#include <moveit_visual_tools/moveit_visual_tools.h>

// All source files that use ROS logging should define a file-specific
// static const rclcpp::Logger named LOGGER, located at the top of the file
// and inside the namespace with the narrowest scope (if there is one)
static const rclcpp::Logger LOGGER = rclcpp::get_logger("move_group_demo");

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions node_options;
  node_options.automatically_declare_parameters_from_overrides(true);
  auto move_group_node = rclcpp::Node::make_shared("move_group_interface_tutorial", node_options);

  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(move_group_node);
  std::thread([&executor]() { executor.spin(); }).detach();


  static const std::string PLANNING_GROUP = "arm";

  moveit::planning_interface::MoveGroupInterface move_group(move_group_node, PLANNING_GROUP);


  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  const moveit::core::JointModelGroup* joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);


  RCLCPP_INFO(LOGGER, "Planning frame: %s", move_group.getPlanningFrame().c_str());


  RCLCPP_INFO(LOGGER, "End effector link: %s", move_group.getEndEffectorLink().c_str());

  // We can get a list of all the groups in the robot:
  RCLCPP_INFO(LOGGER, "Available Planning Groups:");
  std::copy(move_group.getJointModelGroupNames().begin(), move_group.getJointModelGroupNames().end(),
            std::ostream_iterator<std::string>(std::cout, ", "));


  geometry_msgs::msg::PoseStamped target_pose1 = move_group.getPoseTarget("cabin_joint");

  RCLCPP_INFO(LOGGER, "x : %f, y: %f, z: %f", target_pose1.pose.position.x, target_pose1.pose.position.y, target_pose1.pose.position.z);

  //
  // move_group.setPoseTarget(target_pose1);
  //

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  std::vector<double> joint_group_positions;
  move_group.getJointValueTarget(joint_group_positions);
  RCLCPP_INFO(LOGGER, "1: %f", joint_group_positions.at(0));
  // current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

  // bool success = (move_group.plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);
  //
  // RCLCPP_INFO(LOGGER, "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");






  rclcpp::shutdown();
  return 0;
}