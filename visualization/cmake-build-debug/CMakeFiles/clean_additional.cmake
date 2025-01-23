# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "motion_planning_rviz_plugin/CMakeFiles/moveit_motion_planning_rviz_plugin_autogen.dir/AutogenUsed.txt"
  "motion_planning_rviz_plugin/CMakeFiles/moveit_motion_planning_rviz_plugin_autogen.dir/ParseCache.txt"
  "motion_planning_rviz_plugin/CMakeFiles/moveit_motion_planning_rviz_plugin_core_autogen.dir/AutogenUsed.txt"
  "motion_planning_rviz_plugin/CMakeFiles/moveit_motion_planning_rviz_plugin_core_autogen.dir/ParseCache.txt"
  "motion_planning_rviz_plugin/moveit_motion_planning_rviz_plugin_autogen"
  "motion_planning_rviz_plugin/moveit_motion_planning_rviz_plugin_core_autogen"
  "planning_scene_rviz_plugin/CMakeFiles/moveit_planning_scene_rviz_plugin_autogen.dir/AutogenUsed.txt"
  "planning_scene_rviz_plugin/CMakeFiles/moveit_planning_scene_rviz_plugin_autogen.dir/ParseCache.txt"
  "planning_scene_rviz_plugin/CMakeFiles/moveit_planning_scene_rviz_plugin_core_autogen.dir/AutogenUsed.txt"
  "planning_scene_rviz_plugin/CMakeFiles/moveit_planning_scene_rviz_plugin_core_autogen.dir/ParseCache.txt"
  "planning_scene_rviz_plugin/moveit_planning_scene_rviz_plugin_autogen"
  "planning_scene_rviz_plugin/moveit_planning_scene_rviz_plugin_core_autogen"
  "robot_state_rviz_plugin/CMakeFiles/moveit_robot_state_rviz_plugin_autogen.dir/AutogenUsed.txt"
  "robot_state_rviz_plugin/CMakeFiles/moveit_robot_state_rviz_plugin_autogen.dir/ParseCache.txt"
  "robot_state_rviz_plugin/CMakeFiles/moveit_robot_state_rviz_plugin_core_autogen.dir/AutogenUsed.txt"
  "robot_state_rviz_plugin/CMakeFiles/moveit_robot_state_rviz_plugin_core_autogen.dir/ParseCache.txt"
  "robot_state_rviz_plugin/moveit_robot_state_rviz_plugin_autogen"
  "robot_state_rviz_plugin/moveit_robot_state_rviz_plugin_core_autogen"
  "rviz_plugin_render_tools/CMakeFiles/moveit_rviz_plugin_render_tools_autogen.dir/AutogenUsed.txt"
  "rviz_plugin_render_tools/CMakeFiles/moveit_rviz_plugin_render_tools_autogen.dir/ParseCache.txt"
  "rviz_plugin_render_tools/moveit_rviz_plugin_render_tools_autogen"
  "trajectory_rviz_plugin/CMakeFiles/moveit_trajectory_rviz_plugin_autogen.dir/AutogenUsed.txt"
  "trajectory_rviz_plugin/CMakeFiles/moveit_trajectory_rviz_plugin_autogen.dir/ParseCache.txt"
  "trajectory_rviz_plugin/CMakeFiles/moveit_trajectory_rviz_plugin_core_autogen.dir/AutogenUsed.txt"
  "trajectory_rviz_plugin/CMakeFiles/moveit_trajectory_rviz_plugin_core_autogen.dir/ParseCache.txt"
  "trajectory_rviz_plugin/moveit_trajectory_rviz_plugin_autogen"
  "trajectory_rviz_plugin/moveit_trajectory_rviz_plugin_core_autogen"
  )
endif()
