# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "motion_planning_rviz_plugin/CMakeFiles/excavator_motion_planning_rviz_plugin_autogen.dir/AutogenUsed.txt"
  "motion_planning_rviz_plugin/CMakeFiles/excavator_motion_planning_rviz_plugin_autogen.dir/ParseCache.txt"
  "motion_planning_rviz_plugin/CMakeFiles/excavator_motion_planning_rviz_plugin_core_autogen.dir/AutogenUsed.txt"
  "motion_planning_rviz_plugin/CMakeFiles/excavator_motion_planning_rviz_plugin_core_autogen.dir/ParseCache.txt"
  "motion_planning_rviz_plugin/excavator_motion_planning_rviz_plugin_autogen"
  "motion_planning_rviz_plugin/excavator_motion_planning_rviz_plugin_core_autogen"
  )
endif()
