# fabric_capabilities

Provides capabiilites2 runners for fabric stack.

## Supported Runners

| Runner | Description  |
| ---    | ---          |
| Completion runner | informs fabric about FSM completion |
| Set plan runner | adds a new execution plan to the queue of Fabric  |

## Examples

Examples depend on [CollaborativeRoboticsLab/capabilities2](https://github.com/CollaborativeRoboticsLab/capabilities2) and [CollaborativeRoboticsLab/prompt_tools](https://github.com/CollaborativeRoboticsLab/prompt_tools). Following examples have been tested against turtlebot3 simulation using [CollaborativeRoboticsLab/turtlebot3-docker](https://github.com/CollaborativeRoboticsLab/turtlebot3-docker). This is compatible with any robot that uses Nav2 Stack.

| Example | Description |
| ---     | ---         |
| [generative_1.xml](./plans/generative_1.xml) | In this example (2.0, -0.5) point is reachable. The LLM would need to generate a plan that moves the robot to the point. |
| [generative_2.xml](./plans/generative_2.xml) | In this example (2.0, -0.5), (0.0, 2.0), (-2.0, 0.0), (0.0, -2.0) points are reachable. The LLM would need to generate a plan that moves the robot through the points in order. |
| [generative_3.xml](./plans/generative_3.xml) | In this example, the robot is suppoed to go through (2.0, -0.5), (1.0, 3.0), (-2.0, 0.0), (0.0, -2.0) points. Out of these (1.0, 3.0) is unreachable. The LLM would need to generate a plan that moves the robot through the points in order considering the unreachable point |
| [generative_4.xml](./plans/generative_4.xml) | In this example, the robot is suppoed to go through (2.0, -0.5), (1.0, 3.0), (-3.0, -1.0), (0.0, -2.0) points. Out of these (1.0, 3.0) and (-3.0, -1.0) are unreachable. So instead of (1.0, 3.0) robot will move to (0.0, 2.0). Instead of (-3.0, -1.0) the robot will move to (-2.0, 0.0). The LLM would need to generate a plan that moves the robot through the points in order considering the unreachable point. |
| [generative_5.xml](./plans/generative_5.xml) | In this example, the robot is suppoed to go through (2.0, -0.5), (1.0, 3.0), (-3.0, -1.0), (0.0, -2.0) points. Out of these (1.0, 3.0) and (-3.0, -1.0) are unreachable. So instead of (1.0, 3.0) robot will move to (0.0, 2.0). Instead of (-3.0, -1.0) the robot will move to (-2.0, 0.0). (0.0, -2.0) has a recovery location but the position is reachable. The LLM would need to generate a plan that moves the robot through the points in order considering the unreachable point.|

To run the examples, first make sure that the simulation is running and then on different terminals run,

```bash
source install/setup.bash
ros2 launch capabilities2_server capabilities2_server.launch.py
```

```bash
export OPENAI_API_KEY=
source install/setup.bash
ros2 launch prompt_bridge prompt_bridge.launch.py
```

```bash
source install/setup.bash
ros2 launch fabric_capabilities system.launch.py filename:=generative_1.xml
```
Change `filename:=generative_1.xml` to match the correct plan