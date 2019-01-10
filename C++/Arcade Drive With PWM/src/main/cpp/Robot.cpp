/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include "rev/SparkMax.h"

class Robot : public frc::TimedRobot {
  /**
   * In PWM mode, SPARK MAX controllers are intialized by creating a
   * SparkMax object and passing the PWM channel as a parameter
   * 
   * Change the PWM channels below to match your setup
   */
  static const int leftPwmChannel = 0, rightPwmChannel = 1;
  rev::SparkMax m_leftMotor{leftPwmChannel};
  rev::SparkMax m_rightMotor{rightPwmChannel};

  frc::DifferentialDrive m_robotDrive{m_leftMotor, m_rightMotor};
  frc::Joystick m_stick{0};

 public:
  void TeleopPeriodic() {
    // Drive with arcade style
    m_robotDrive.ArcadeDrive(-m_stick.GetY(), m_stick.GetX());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
