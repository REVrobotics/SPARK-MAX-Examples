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
 public:
  Robot() { }

  void TeleopPeriodic() override {
    // set the motor output based on jostick position
    m_motor.Set(m_stick.GetY());

    // Read the position from the encoder.
    frc::SmartDashboard::PutNumber("Encoder Position", m_encoder.GetPosition());

    // Read the velocity from the encoder.
    frc::SmartDashboard::PutNumber("Encoder Rate", m_encoder.GetVelocity());
  }

 private:
  /**
   * The motor object is constructed with 2 parameters, a CAN device ID and a 
   * motor type
   * 
   * The CAN ID is configured using the SPARK MAX Client, and defaults to 0
   * 
   * The motor type can either be kBrushless or kBrushed
   */
  rev::CANSparkMax m_motor{1, rev::CANSparkMax::MotorType::kBrushless};

  /**
   * In order to read encoder values an encoder object is created using the 
   * GetEncoder() method from an existing CANSparkMax object
   */
  rev::CANEncoder m_encoder = m_motor.GetEncoder();

  frc::Joystick m_stick{0};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
