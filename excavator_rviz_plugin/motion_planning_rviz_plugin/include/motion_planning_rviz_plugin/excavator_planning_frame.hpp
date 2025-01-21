//
// Created by root on 1/20/25.
//

#ifndef EXCAVATOR_PLANING_FRAME_HPP
#define EXCAVATOR_PLANING_FRAME_HPP

#pragma once

#include <QWidget>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>

#ifndef Q_MOC_RUN
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <rviz_default_plugins/displays/interactive_markers/interactive_marker.hpp>
#include <visualization_msgs/msg/interactive_marker_update.hpp>


#include <rclcpp/logger.hpp>
#endif

#include <map>
#include <string>
#include <memory>

namespace rviz_common
{
class DisplayContext;
}

namespace Ui
{
class MotionPlanningUI;
}

namespace excavator_rviz_plugin
{
class ExcavatorPlanningDisplay;

const std::string OBJECT_RECOGNITION_ACTION = "/recognize_objects";

static const double LARGE_MESH_THRESHOLD = 10.0;

class ExcavatorPlaningFrame : public QWidget
{
friend class ExcavatorPlanningDisplay;
Q_OBJECT
public:
  ExcavatorPlaningFrame(const ExcavatorPlanningFrame&) = delete;
  ExcavatorPlaningFrame(QWidget* parent = 0);
  ~ExcavatorPlaningFrame() override;

protected:
  moveit::planning_interface::MoveGroupInterfacePtr move_group_;
  moveit::planning_interface::MoveGroupInterface::PlanPtr current_plan_;

private:


  QPushButton* button_planning_;
  geometry_msgs::msg::PoseStamped goal_pose_;

  rclcpp::Subscription<visualization_msgs::msg::InteractiveMarkerUpdate>::SharedPtr interactive_marker_sub_;

  rclcpp::Node::SharedPtr node_;
  rclcpp::Logger logger_;

};

}


#endif //EXCAVATOR_PLANING_FRAME_HPP
