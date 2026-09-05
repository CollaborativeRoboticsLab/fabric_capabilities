# Fabric Capabilities

Provides capabilities2 runners for the fabric stack. This package owns examples whose primary outcome is generating an executable plan, including integrations that first gather prompt context and then call `FabricGeneratePlanRunner`.

## Supported Runners

| Runner | Feature Focus | Description |
| --- | --- | --- |
| `FabricCompletionRunner` | System Functionality | informs the fabric server about execution completion |
| `FabricGeneratePlanRunner` | Plan Generation | sends a natural-language task, plus optional prompt-cache UUID, to fabric for plan generation |

## Examples

The package contains both direct fabric-generation examples and prompt-assisted fabric-generation examples.

| Example | Description |
| ---     | ---         |
| [nav2_generative_1.xml](./plans/nav2_generative_1.xml) | Generate a navigation plan to move the robot to a reachable point. |
| [nav2_generative_2.xml](./plans/nav2_generative_2.xml) | Generate a navigation plan that moves the robot through multiple reachable points in order. |
| [nav2_generative_3.xml](./plans/nav2_generative_3.xml) | Generate a navigation plan that must account for one unreachable waypoint. |
| [nav2_generative_4.xml](./plans/nav2_generative_4.xml) | Generate a navigation plan that must account for multiple unreachable waypoints. |
| [nav2_generative_5.xml](./plans/nav2_generative_5.xml) | Generate a navigation plan with unreachable waypoints and recovery-aware behavior. |
| [gripper_generative_1.xml](./plans/gripper_generative_1.xml) | Prompt current gripper state, then generate a plan to open the gripper. |
| [moveit2_generative_1.xml](./plans/moveit2_generative_1.xml) | Prompt current Cartesian pose, then generate a plan to move the gripper 5 cm backward. |
| [moveit2_generative_2.xml](./plans/moveit2_generative_2.xml) | Prompt current manipulator joint pose, then generate a plan to rotate `wrist_1` by 45 degrees clockwise. |
| [moveit2_generative_3.xml](./plans/moveit2_generative_3.xml) | Generate a plan to move the robot to named pose `pre_grasp`. |
| [moveit2_generative_4.xml](./plans/moveit2_generative_4.xml) | Generate a plan to move the robot through named poses `pre_grasp`, `grasp_pose`, and `post_grasp`. |

> Note: The examples are designed to work and has been tested with the turtlebot3 world in Gazebo, but on the assumption that the start position of the robot is (0.0, 0.5) in gazebo simulation. In ROS `humble` this is the default, but in `jazzy` you might need to change the initial position of the robot in the world file to match this. If you use [CollaborativeRoboticsLab/turtlebot3-docker](https://github.com/CollaborativeRoboticsLab/turtlebot3-docker), it is already set to this position.

## Build

```bash
cd ~/colcon_ws/src
git clone https://github.com/CollaborativeRoboticsLab/capabilities2.git
git clone https://github.com/CollaborativeRoboticsLab/fabric.git
git clone https://github.com/CollaborativeRoboticsLab/prompt_tools.git
git clone https://github.com/CollaborativeRoboticsLab/prompt_capabilities.git
git clone https://github.com/CollaborativeRoboticsLab/nav2_capabilities.git
git clone https://github.com/CollaborativeRoboticsLab/fabric_capabilities.git

cd ~/colcon_ws
colcon build --symlink-install
```

To setup the simulation, you can use the turtlebot3 world in Gazebo. You can launch the simulation using the following command,

```bash
git clone https://github.com/CollaborativeRoboticsLab/turtlebot3-docker.git
cd turtlebot3-docker/docker
docker compose pull
xhost +local:root
docker compose up
```

## Running the examples

To run the examples, first make sure that the simulation is running.

For non-generative execution plans, a single launch is enough because the wrapper now includes Fabric, Capabilities2, and prompt tools by default:

```bash
source install/setup.bash
ros2 launch fabric_capabilities system.launch.py filename:=nav2_generative_1.xml
```

For prompt-based generation, the same launch already starts prompt tools by default.
Replace <your_openai_api_key> with your actual OpenAI API key before launching.

```bash
export OPENAI_API_KEY=<your_openai_api_key>
source install/setup.bash
ros2 launch fabric_capabilities system.launch.py filename:=nav2_generative_1.xml
```

If you do not want `prompt_bridge` in this launch graph, add `start_prompt_tools:=false`.

If you also want Experience and Supervisor in the same launch graph, add `start_experience_stack:=true`.

Change `filename:=nav2_generative_1.xml` to any other file from the table above.

## Citation

If you use this work in an academic context, please cite the following publication(s):

```bibtex
@misc{ratnayake2026gpsfsm,
  title={A Generative Partially Specified Finite State Machine Approach to Complex Behaviour Planning}, 
  author={Kalana Ratnayake and Michael Pritchard and David Hinwood and Maleen Jayasuriya and Damith Herath},
  year={2026},
  eprint={2607.15674},
  archivePrefix={arXiv},
  primaryClass={cs.RO},
  url={https://arxiv.org/abs/2607.15674}, 
}
```
