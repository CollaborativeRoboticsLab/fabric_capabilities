# Interface Information

Following are the details of the interfaces provided by the Fabric Capabilities package. A runner that intends to connect with one of these interfaces should support the input and ouput parameters described below.

## CompletionRunner

Input Parameters:

| Parameter Name    | Type   | Description |
| ---               | ---    | ---         |
| plan_id           | string | The ID of the plan to be completed. |

Output Parameters:

None

## SetPlanRunner

Input Parameters:

| Parameter Name   | Type   | Description |
| ---              | ---    | ---         |
| plan             | string | The plan to be set for the next iteration. |


Output Parameters:

None