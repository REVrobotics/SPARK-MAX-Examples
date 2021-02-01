# Motor Follower

### Description
This example shows how to control multiple motors simultaneously, specifically how to set motors to follow another motor and mirror the lead motor's actions.

### Usage
Set the variables at the beginning of the example to match your setup.
- `leadDeviceID` - CAN device ID for lead motor
- `followDeviceID` - CAN device ID for follower motor
- `kJoystickPort` - Joystick device port number

Control the motors' velocities by moving the joystick up or down.

Both motors will run accordingly.