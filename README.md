# fabric_capabilities

Provides capabiilites2 runners for fabric stack.

## Supported Runners

| Runner | Description  |
| ---    | ---          |
| Completion runner | informs fabric about FSM completion |
| Set plan runner | adds a new execution plan to the queue of Fabric  |

## Examples

Examples depend on [CollaborativeRoboticsLab/capabilities2](https://github.com/CollaborativeRoboticsLab/capabilities2) and [CollaborativeRoboticsLab/prompt_tools](https://github.com/CollaborativeRoboticsLab/prompt_tools)


| Example | Description |
| ---     | ---         |
| [Example 1](./docs/example1.md) | Implements moving the robot to a given coordinate |
| [Example 2](./docs/example2.md) | Implements moving the robot through a sequence of given coordinates, which are all reachable |
| [Example 3](./docs/example3.md) | Implements moving the robot through a sequence of given coordinates, where one is unreachable with one recovery action |
| [Example 4](./docs/example4.md) | Implements moving the robot through a sequence of given coordinates, where two are unreachable with two recoveries |
| [Example 5](./docs/example5.md) | Implements moving the robot through a sequence of given coordinates, where two are unreachable, but all contains recovery actions. |

To run the examples

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