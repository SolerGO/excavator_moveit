//
// Created by root on 1/20/25.
//

#ifndef EXCAVATOR_PLANING_FRAME_HPP
#define EXCAVATOR_PLANING_FRAME_HPP

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#ifndef Q_MOC_RUN
#include <moveit/macros/class_forward.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene_monitor/planning_scene_monitor.hpp>
#include <moveit/robot_interaction/robot_interaction.hpp>
#include <moveit/robot_interaction/interaction_handler.hpp>

#include <interactive_markers/interactive_marker_server.hpp>
#include <rviz_default_plugins/displays/interactive_markers/interactive_marker.hpp>
#include <moveit_msgs/msg/motion_plan_request.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <object_recognition_msgs/action/object_recognition.hpp>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/empty.hpp>
#include <std_srvs/srv/empty.hpp>
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

namespace moveit_warehouse
{
MOVEIT_CLASS_FORWARD(PlanningSceneStorage);  // Defines PlanningSceneStoragePtr, ConstPtr, WeakPtr... etc
MOVEIT_CLASS_FORWARD(ConstraintsStorage);    // Defines ConstraintsStoragePtr, ConstPtr, WeakPtr... etc
MOVEIT_CLASS_FORWARD(RobotStateStorage);     // Defines RobotStateStoragePtr, ConstPtr, WeakPtr... etc
}  // namespace moveit_warehouse

namespace moveit_rviz_plugin
{

class MotionPlanningDisplay;
class MotionPlanningFrameJointsWidget;

class ExcavatorPlanningFrame : public QWidget
{
  friend class MotionPlanningDisplay;
  Q_OBJECT
public:
  ExcavatorPlanningFrame(const ExcavatorPlanningFrame&) = delete;
  ExcavatorPlanningFrame(MotionPlanningDisplay* pdisplay, rviz_common::DisplayContext* context, QWidget* parent = nullptr);
  ~ExcavatorPlanningFrame() override;

  void clearRobotModel();
  void changePlanningGroup();
  void enable();
  void disable();
  void sceneUpdate(planning_scene_monitor::PlanningSceneMonitor::SceneUpdateType update_type);

protected:

  void updateSceneMarkers(double wall_dt, double ros_dt);
  void updateExternalCommunication();

  MotionPlanningDisplay* planning_display_;
  rviz_common::DisplayContext* context_;

  moveit::planning_interface::MoveGroupInterfacePtr move_group_;

  moveit::planning_interface::MoveGroupInterface::PlanPtr current_plan_;
  moveit_warehouse::PlanningSceneStoragePtr planning_scene_storage_;

  std::shared_ptr<rviz_default_plugins::displays::InteractiveMarker> scene_marker_;

  QPushButton* button_planning_;
  QLabel* label_;



Q_SIGNALS:
  void planningFinished();
  void configChanged();



private Q_SLOT:
  void buttonPlanningClicked();
  void onNewPlanningSceneState();
  void computePlanButtonClicked();
  bool computeCartesianPlan();
  bool computeJointSpacePlan();


private:
  void fillPlanningGroupOptions();
  void changePlanningGroupHelper();
  void fillStateSelectionOptions();
  void populateConstraintsList();
  void populateConstraintsList(const std::vector<std::string>& constr);
  void configureForPlanning();

  rclcpp::Node::SharedPtr node_;
  rclcpp::Logger logger_;

  bool first_time_;
};

}


#endif //EXCAVATOR_PLANING_FRAME_HPP
