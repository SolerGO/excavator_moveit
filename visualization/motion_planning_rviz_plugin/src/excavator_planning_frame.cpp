//
// Created by root on 1/20/25.
//

#include <functional>

#include <moveit/common_planning_interface_objects/common_objects.hpp>
#include <moveit/motion_planning_rviz_plugin/excavator_planning_frame.hpp>
#include <moveit/motion_planning_rviz_plugin/motion_planning_display.hpp>
#include <moveit/move_group/capability_names.hpp>
#include <moveit/utils/logger.hpp>
#include <moveit/robot_state/robot_state.hpp>

#include <moveit/kinematic_constraints/utils.hpp>
#include <moveit/robot_state/conversions.hpp>

#include <std_srvs/srv/empty.hpp>
#include <moveit_msgs/msg/robot_state.hpp>
#include <tf2_eigen/tf2_eigen.hpp>
#include <moveit/trajectory_processing/time_optimal_trajectory_generation.hpp>

#include <geometric_shapes/shape_operations.h>

#include <rviz_common/display_context.hpp>
#include <rviz_common/frame_manager_iface.hpp>
#include <tf2_ros/buffer.h>

#include <std_srvs/srv/empty.hpp>

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QComboBox>
#include <QShortcut>

namespace moveit_rviz_plugin
{
ExcavatorPlanningFrame::ExcavatorPlanningFrame(MotionPlanningDisplay* pdisplay, rviz_common::DisplayContext* context,
                                      QWidget* parent)
    : QWidget(parent)
    , planning_display_(pdisplay)
    , context_(context)
    , logger_(moveit::getLogger("moveit.ros.motion_planning_frame"))
    , first_time_(true)
  {
    auto ros_node_abstraction = context_->getRosNodeAbstraction().lock();
    if (!ros_node_abstraction)
    {
      RCLCPP_INFO(logger_, "Unable to lock weak_ptr from DisplayContext in MotionPlanningFrame constructor");
      return;
    }
    node_ = ros_node_abstraction->get_raw_node();

    planning_display_->useApproximateIK(true);

    const auto layout = new QVBoxLayout(this);
    label_ = new QLabel("Сплонировать путь");
    button_planning_ = new QPushButton("Ожидание команды");
    layout->addWidget(button_planning_);
    layout->addWidget(label_);
    connect(button_planning_, &QPushButton::clicked, this, &ExcavatorPlanningFrame::buttonPlanningClicked);
  }

  ExcavatorPlanningFrame::~ExcavatorPlanningFrame() = default;



  void ExcavatorPlanningFrame::buttonPlanningClicked()
  {
    planning_display_->addBackgroundJob([this] { computePlanButtonClicked(); }, "compute plan");
  }

  void ExcavatorPlanningFrame::clearRobotModel(){
    move_group_.reset();
  }

  void ExcavatorPlanningFrame::changePlanningGroup(){
    planning_display_->addBackgroundJob([this] { changePlanningGroupHelper(); }, "Frame::changePlanningGroup");
  }

  void ExcavatorPlanningFrame::enable(){
    const std::string new_ns = planning_display_->getMoveGroupNS();
    if (node_->get_namespace() != new_ns)
    {
      RCLCPP_INFO(logger_, "MoveGroup namespace changed: %s -> %s. Reloading params.", node_->get_namespace(),
                  new_ns.c_str());
    }

    // activate the frame
    if (parentWidget())
      parentWidget()->show();
  }


  void ExcavatorPlanningFrame::disable()
  {
    move_group_.reset();
    scene_marker_.reset();
    if (parentWidget())
      parentWidget()->hide();
  }

  void ExcavatorPlanningFrame::sceneUpdate(planning_scene_monitor::PlanningSceneMonitor::SceneUpdateType update_type){

  }


  void ExcavatorPlanningFrame::updateSceneMarkers(double wall_dt, double ros_dt){
    if (scene_marker_)
      scene_marker_->update();
  }

  void ExcavatorPlanningFrame::updateExternalCommunication(){
    planning_display_->getRobotInteraction()->toggleMoveInteractiveMarkerTopic(true);
  }

  void ExcavatorPlanningFrame::onNewPlanningSceneState(){
    moveit::core::RobotState current(planning_display_->getPlanningSceneRO()->getCurrentState());
    planning_display_->setQueryStartState(current);
    planning_display_->rememberPreviousStartState();
    planning_display_->setQueryGoalState(current);
  }

  void ExcavatorPlanningFrame::fillPlanningGroupOptions(){

  }

  void ExcavatorPlanningFrame::changePlanningGroupHelper(){
    if (!planning_display_->getPlanningSceneMonitor())
        return;

    planning_display_->addMainLoopJob([this] { fillStateSelectionOptions(); });
    planning_display_->addMainLoopJob([this]() { populateConstraintsList(std::vector<std::string>()); });

    const moveit::core::RobotModelConstPtr& robot_model = planning_display_->getRobotModel();
    std::string group = planning_display_->getCurrentPlanningGroup();

    if (!group.empty() && robot_model)
    {
      RCLCPP_INFO(logger_, "group %s", group.c_str());
      if (move_group_ && move_group_->getName() == group)
        return;
      RCLCPP_INFO(logger_, "Constructing new MoveGroup connection for group '%s' in namespace '%s'", group.c_str(),
                  planning_display_->getMoveGroupNS().c_str());
      moveit::planning_interface::MoveGroupInterface::Options opt(
          group, moveit::planning_interface::MoveGroupInterface::ROBOT_DESCRIPTION, planning_display_->getMoveGroupNS());
      opt.robot_model = robot_model;
      opt.robot_description.clear();
      try
      {
  #ifdef RVIZ_TF1
        std::shared_ptr<tf2_ros::Buffer> tf_buffer = moveit::planning_interface::getSharedTF();
  #else
        //@note: tf2 no longer accessible?
        // /std::shared_ptr<tf2_ros::Buffer> tf_buffer = context_->getFrameManager()->getTF2BufferPtr();
        std::shared_ptr<tf2_ros::Buffer> tf_buffer = moveit::planning_interface::getSharedTF();
  #endif
        move_group_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(
            node_, opt, tf_buffer, rclcpp::Duration::from_seconds(30));
      }
      catch (std::exception& ex)
      {
        RCLCPP_ERROR(logger_, "%s", ex.what());
      }
      if (move_group_)
      {
        move_group_->allowLooking(true);
        move_group_->allowReplanning(true);
        bool has_unique_endeffector = !move_group_->getEndEffectorLink().empty();
        std::vector<moveit_msgs::msg::PlannerInterfaceDescription> desc;
        planning_display_->addBackgroundJob([this]() { populateConstraintsList(); }, "populateConstraintsList");

        if (first_time_)
        {
          first_time_ = false;
          const planning_scene_monitor::LockedPlanningSceneRO& ps = planning_display_->getPlanningSceneRO();
          if (ps)
          {
            planning_display_->setQueryStartState(ps->getCurrentState());
            planning_display_->setQueryGoalState(ps->getCurrentState());
          }
          // This ensures saved UI settings applied after planning_display_ is ready
          planning_display_->useApproximateIK(true);
        }
      }
    }
  }

  void ExcavatorPlanningFrame::fillStateSelectionOptions(){


    if (!planning_display_->getPlanningSceneMonitor())
      return;

    const moveit::core::RobotModelConstPtr& robot_model = planning_display_->getRobotModel();
    std::string group = planning_display_->getCurrentPlanningGroup();
    if (group.empty())
      return;
    const moveit::core::JointModelGroup* jmg = robot_model->getJointModelGroup(group);
  }

  void ExcavatorPlanningFrame::populateConstraintsList(){
    if (move_group_)
      planning_display_->addMainLoopJob([this]() { populateConstraintsList(move_group_->getKnownConstraints()); });
  }

  void ExcavatorPlanningFrame::populateConstraintsList(const std::vector<std::string>& constr){

  }

  void ExcavatorPlanningFrame::computePlanButtonClicked(){
    if (!move_group_)
      return;

    // Clear status
    label_->setText("Планирование...");

    configureForPlanning();
    planning_display_->rememberPreviousStartState();
    bool success = false ? computeCartesianPlan() : computeJointSpacePlan();

    if (success)
    {
      label_->setText("Success");
    }
    else
    {
      current_plan_.reset();
      label_->setText("Failed");
    }
    Q_EMIT planningFinished();
  }

  void ExcavatorPlanningFrame::configureForPlanning()
  {
    move_group_->setStartState(*planning_display_->getQueryStartState());
    move_group_->setJointValueTarget(*planning_display_->getQueryGoalState());
    move_group_->setPlanningTime(20.0);
    move_group_->setNumPlanningAttempts(10);
    move_group_->setMaxVelocityScalingFactor(0.5);
    move_group_->setMaxAccelerationScalingFactor(0.5);
    // configureWorkspace();
    if (static_cast<bool>(planning_display_))
      planning_display_->dropVisualizedTrajectory();
  }

  bool ExcavatorPlanningFrame::computeCartesianPlan(){
    // rclcpp::Time start = rclcpp::Clock().now();
    // // get goal pose
    // moveit::core::RobotState goal = *planning_display_->getQueryGoalState();
    // std::vector<geometry_msgs::msg::Pose> waypoints;
    // const std::string& link_name = move_group_->getEndEffectorLink();
    // const moveit::core::LinkModel* link = move_group_->getRobotModel()->getLinkModel(link_name);
    // if (!link)
    // {
    //   RCLCPP_ERROR_STREAM(logger_, "Failed to determine unique end-effector link: " << link_name);
    //   return false;
    // }
    // waypoints.push_back(tf2::toMsg(goal.getGlobalLinkTransform(link)));
    //
    // // setup default params
    // double cart_step_size = 0.01;
    // bool avoid_collisions = true;
    //
    // // compute trajectory
    // moveit_msgs::msg::RobotTrajectory trajectory;
    // double fraction = move_group_->computeCartesianPath(waypoints, cart_step_size, trajectory, avoid_collisions);
    //
    // if (fraction >= 1.0)
    // {
    //   RCLCPP_INFO(logger_, "Achieved %f %% of Cartesian path", fraction * 100.);
    //
    //   // Compute time parameterization to also provide velocities
    //   // https://groups.google.com/forum/#!topic/moveit-users/MOoFxy2exT4
    //   robot_trajectory::RobotTrajectory rt(move_group_->getRobotModel(), move_group_->getName());
    //   rt.setRobotTrajectoryMsg(*move_group_->getCurrentState(), trajectory);
    //   trajectory_processing::TimeOptimalTrajectoryGeneration time_parameterization;
    //   bool success = time_parameterization.computeTimeStamps(rt, 0.5, 0.5);
    //   RCLCPP_INFO(logger_, "Computing time stamps %s", success ? "SUCCEEDED" : "FAILED");
    //
    //   // Store trajectory in current_plan_
    //   current_plan_ = std::make_shared<moveit::planning_interface::MoveGroupInterface::Plan>();
    //   rt.getRobotTrajectoryMsg(current_plan_->trajectory);
    //   current_plan_->planning_time = (rclcpp::Clock().now() - start).seconds();
    //   return success;
    // }
    // return false;
  }

  bool ExcavatorPlanningFrame::computeJointSpacePlan(){
    current_plan_ = std::make_shared<moveit::planning_interface::MoveGroupInterface::Plan>();
    return move_group_->plan(*current_plan_) == moveit::core::MoveItErrorCode::SUCCESS;
  }



}
