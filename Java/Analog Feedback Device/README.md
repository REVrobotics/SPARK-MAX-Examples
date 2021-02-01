# Analog Feedback Device

### Description
This example shows how to use an analog sensor as the feedback device for the PID controller of a REV NEO Brushless Motor instead of the NEO's built-in hall sensor. For demonstration, the PID controller will be used to set the motor position.

### Usage
Set the variables at the beginning of the example to match your setup.
- `deviceID` - CAN device ID

PID Coefficients can be adjusted on SmartDashboard as well as the set rotations (position setpoint). 

The setpoint and process variable will be displayed on SmartDashboard.