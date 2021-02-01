# Smart Motion Example

### Description
This example shows how to use REV Smart Motion to control the position of the motor in a smooth and predictable manner by generating a motion profile on the fly in the SPARK MAX and controlling the velocity of the motor to follow that profile.

The example will use ShuffleBoard to graph the inputs and outputs such as process variable, setpoint, and applied output to easily visualize what is happening.

### Usage
Set the variables at the beginning of the example to match your setup.
- `deviceID` - CAN device ID

Use the "Mode" button on SmartDashboard to toggle between velocity and Smart Motion modes.

PID coefficients and Smart Motion coefficients can be adjusted on SmartDashboard as well as the velocity and position setpoints.

The setpoint, process variable, and the motor's applied output will be displayed on SmartDashboard.
