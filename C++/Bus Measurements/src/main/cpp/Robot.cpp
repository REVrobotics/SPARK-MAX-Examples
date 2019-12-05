/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/smartdashboard.h>
#include "rev/CANSparkMax.h"



class Robot : public frc::TimedRobot {


  // Here we define parameters that will be used to initialize a SparkMax 
  // object. We set the device ID to 1, and the motor type to brushless.
  // Change these parameters to match your setup.
  static const int deviceID = 1;
  static const auto motorType = rev::CANSparkMax::MotorType::kBrushless; // can also be kBrushed

  // Initialize a SparkMax object called m_motor with the given parameters.
  rev::CANSparkMax m_motor{deviceID, motorType};

  // For motor control, we use a single joystick in this example. Plug in any 
  // controller and use the joystick to control motor output when the robot is
  // enabled.
  frc::Joystick m_stick{0};

public:
  void RobotPeriodic() {
    // There are several useful bus measurements you can get from the SparkMax.
    // This includes bus voltage (V), output current (A), Applied Output 
    // (duty cycle), and motor temperature (C)
    double busVoltage = m_motor.GetBusVoltage();
    double current = m_motor.GetOutputCurrent();
    double appliedOut = m_motor.GetAppliedOutput();
    double temperature = m_motor.GetMotorTemperature();

    // Open the SmartDashboard when your program is running to see the values
    frc::SmartDashboard::PutNumber("Bus Voltage", busVoltage);
    frc::SmartDashboard::PutNumber("Output Current", current);
    frc::SmartDashboard::PutNumber("Applied Output", appliedOut);
    frc::SmartDashboard::PutNumber("Motor Temperature", temperature);
  }

  void TeleopPeriodic() {
    m_motor.Set(m_stick.GetY());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
