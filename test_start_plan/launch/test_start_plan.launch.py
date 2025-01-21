from launch import LaunchDescription
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():


    # MoveGroupInterface demo executable
    move_group_demo = Node(
        name="test_start_plan",
        package="test_start_plan",
        executable="test_start_plan",
        output="screen",
        parameters=[
            {'use_sim_time': True},
        ],
    )

    return LaunchDescription([move_group_demo])