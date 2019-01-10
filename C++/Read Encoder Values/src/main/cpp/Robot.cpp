/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "rev/CANSparkMax.h"

/**
 * Sample program displaying position and velocity on the SmartDashboard
 * 
 * Position is displayed in revolutions and velocity is displayed in RPM
 */
class Robot : public frc::TimedRobot {
  // initialize SPARK MAX
  static const int deviceID = 1;
  rev::CANSparkMax m_motor{deviceID, rev::CANSparkMax::MotorType::kBrushless};

  /**
   * In order to read encoder values an encoder object is created using the 
   * GetEncoder() method from an existing CANSparkMax object
   */
  rev::CANEncoder m_encoder = m_motor.GetEncoder();

  frc::Joystick m_stick{0};

 public:
  Robot() { }

  void TeleopPeriodic() override {
    // set the motor output based on jostick position
    m_motor.Set(m_stick.GetY());

    /**
     * Encoder position is read from a CANEncoder object by calling the
     * GetPosition() method.
     * 
     * GetPosition() returns the position of the encoder in units of revolutions
     */
    frc::SmartDashboard::PutNumber("Encoder Position", m_encoder.GetPosition());

    /**
     * Encoder velocity is read from a CANEncoder object by calling the
     * GetVelocity() method.
     * 
     * GetVelocity() returns the velocity of the encoder in units of RPM
     */
    frc::SmartDashboard::PutNumber("Encoder Velocity", m_encoder.GetVelocity());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
