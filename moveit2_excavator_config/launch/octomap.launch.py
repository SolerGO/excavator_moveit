import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, EmitEvent, RegisterEventHandler, OpaqueFunction
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessExit
from launch.events import Shutdown
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():

    # Constants for paths to different files and folders
    package_name_moveit_config = 'moveit2_excavator_config'

    # Launch configuration variables
    use_sim_time = LaunchConfiguration('use_sim_time')
    use_rviz = LaunchConfiguration('use_rviz')

    # Get the package share directory
    pkg_share_moveit_config_temp = FindPackageShare(package=package_name_moveit_config)

    # Declare the launch arguments
    declare_robot_name_cmd = DeclareLaunchArgument(
        name='robot_name',
        default_value='excavator',
        description='Name of the robot to use')

    declare_use_sim_time_cmd = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true')

    def configure_setup(context):
        """Configure MoveIt and create nodes with proper string conversions."""
        # Get the robot name as a string for use in MoveItConfigsBuilder
        robot_name_str = LaunchConfiguration('robot_name').perform(context)

        # Get package path
        pkg_share_moveit_config = pkg_share_moveit_config_temp.find(package_name_moveit_config)

        # Construct file paths using robot name string
        config_path = os.path.join(pkg_share_moveit_config, 'config')

        # Define all config file paths
        initial_positions_file_path = os.path.join(config_path, 'initial_positions.yaml')
        joint_limits_file_path = os.path.join(config_path, 'joint_limits.yaml')
        sensor_3d_file_path = os.path.join(config_path, 'sensor_3d.yaml')
        kinematics_file_path = os.path.join(config_path, 'kinematics.yaml')
        moveit_controllers_file_path = os.path.join(config_path, 'moveit_controllers.yaml')
        srdf_model_path = os.path.join(config_path, f'{robot_name_str}.srdf')
        pilz_cartesian_limits_file_path = os.path.join(config_path, 'pilz_cartesian_limits.yaml')

        # Create MoveIt configuration
        moveit_config = (
            MoveItConfigsBuilder(robot_name_str, package_name=package_name_moveit_config)
            .trajectory_execution(file_path=moveit_controllers_file_path)
            .robot_description_semantic(file_path=srdf_model_path)
            .joint_limits(file_path=joint_limits_file_path)
            .sensors_3d(file_path=sensor_3d_file_path)
            .robot_description_kinematics(file_path=kinematics_file_path)
            .planning_pipelines(
                pipelines=["ompl", "pilz_industrial_motion_planner", "stomp"],
                default_planning_pipeline="ompl"
            )
            .planning_scene_monitor(
                publish_robot_description=False,
                publish_robot_description_semantic=True,
                publish_planning_scene=True,
            )
            .pilz_cartesian_limits(file_path=pilz_cartesian_limits_file_path)
            .to_moveit_configs()
        )

        octomap_config = {'map_frame': 'lidar_link',
                          'octomap_resolution': 0.2,
                          'max_range': 15.0}

        # MoveIt capabilities
        move_group_capabilities = {"capabilities": "move_group/ExecuteTaskSolutionCapability"}

        # Create move_group node
        start_move_group_node_cmd = Node(
            package="moveit_ros_occupancy_map_monitor",
            executable="moveit_ros_occupancy_map_server",
            output="screen",
            parameters=[
                octomap_config
            ],
        )

        return [start_move_group_node_cmd]

    # Create the launch description
    ld = LaunchDescription()

    # Add the launch arguments
    ld.add_action(declare_robot_name_cmd)
    ld.add_action(declare_use_sim_time_cmd)


    # Add the setup and node creation
    ld.add_action(OpaqueFunction(function=configure_setup))

    return ld