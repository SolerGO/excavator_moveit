set(HEADERS
    include/motion_planning_rviz_plugin/excavator_planning_frame.hpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Plugin Source
set(SOURCE_FILES
    src/excavator_planning_frame.cpp
    ../../test_start_plan/src/test_start_plan.cpp
)

add_library(excavator_motion_planning_rviz_plugin_core SHARED
    ${SOURCE_FILES} ${HEADERS})
set_target_properties(excavator_motion_planning_rviz_plugin_core
    PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
target_link_libraries(
    excavator_motion_planning_rviz_plugin_core moveit_rviz_plugin_render_tools
    moveit_planning_scene_rviz_plugin)
ament_target_dependencies(
    excavator_motion_planning_rviz_plugin_core
    moveit_ros_robot_interaction
    moveit_ros_planning_interface
    moveit_ros_warehouse
    rviz2
    rviz_ogre_vendor
    Qt5
    pluginlib)
target_include_directories(excavator_motion_planning_rviz_plugin_core
    PRIVATE "${OGRE_PREFIX_DIR}/include")

add_library(excavator_motion_planning_rviz_plugin SHARED src/plugin_init.cpp)
set_target_properties(excavator_motion_planning_rviz_plugin
    PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
target_link_libraries(excavator_motion_planning_rviz_plugin
    excavator_motion_planning_rviz_plugin_core)
ament_target_dependencies(
    excavator_motion_planning_rviz_plugin moveit_ros_robot_interaction
    moveit_ros_warehouse pluginlib rviz_ogre_vendor)
target_include_directories(excavator_motion_planning_rviz_plugin
    PRIVATE "${OGRE_PREFIX_DIR}/include")

install(DIRECTORY include/ DESTINATION include/excavator_rviz_plugin)