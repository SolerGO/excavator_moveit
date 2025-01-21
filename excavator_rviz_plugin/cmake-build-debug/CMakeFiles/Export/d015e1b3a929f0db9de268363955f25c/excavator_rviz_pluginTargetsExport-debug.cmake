#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "excavator_rviz_plugin::excavator_motion_planning_rviz_plugin" for configuration "Debug"
set_property(TARGET excavator_rviz_plugin::excavator_motion_planning_rviz_plugin APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(excavator_rviz_plugin::excavator_motion_planning_rviz_plugin PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libexcavator_motion_planning_rviz_plugin.so.0.0.1"
  IMPORTED_SONAME_DEBUG "libexcavator_motion_planning_rviz_plugin.so.0.0.1"
  )

list(APPEND _cmake_import_check_targets excavator_rviz_plugin::excavator_motion_planning_rviz_plugin )
list(APPEND _cmake_import_check_files_for_excavator_rviz_plugin::excavator_motion_planning_rviz_plugin "${_IMPORT_PREFIX}/lib/libexcavator_motion_planning_rviz_plugin.so.0.0.1" )

# Import target "excavator_rviz_plugin::excavator_motion_planning_rviz_plugin_core" for configuration "Debug"
set_property(TARGET excavator_rviz_plugin::excavator_motion_planning_rviz_plugin_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(excavator_rviz_plugin::excavator_motion_planning_rviz_plugin_core PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libexcavator_motion_planning_rviz_plugin_core.so.0.0.1"
  IMPORTED_SONAME_DEBUG "libexcavator_motion_planning_rviz_plugin_core.so.0.0.1"
  )

list(APPEND _cmake_import_check_targets excavator_rviz_plugin::excavator_motion_planning_rviz_plugin_core )
list(APPEND _cmake_import_check_files_for_excavator_rviz_plugin::excavator_motion_planning_rviz_plugin_core "${_IMPORT_PREFIX}/lib/libexcavator_motion_planning_rviz_plugin_core.so.0.0.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
