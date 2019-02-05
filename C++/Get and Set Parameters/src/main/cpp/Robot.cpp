/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/smartdashboard.h>
#include "rev/CANSparkMax.h"

class Robot : public frc::TimedRobot {
  /**
   * deviceID is the CAN ID of the SPARK MAX you are using.
   * Change to match your setup
   */
  static const int deviceID = 1;
  rev::CANSparkMax m_motor{deviceID, rev::CANSparkMax::MotorType::kBrushless};

  frc::Joystick m_stick{0};

 public:
  void RobotInit() {
    /**
     * The RestoreFactoryDefaults method can be used to reset the configuration parameters
     * in the SPARK MAX to their factory default state. If no argument is passed, these
     * parameters will not persist between power cycles
     */
    m_motor.RestoreFactoryDefaults();

    /**
     * Parameters can be set by calling the appropriate Set method on the CANSparkMax object
     * whose properties you want to change
     * 
     * Set methods will return one of three CANError values which will let you know if the 
     * parameter was successfully set:
     *  CANError::kOk
     *  CANError::kError
     *  CANError::kTimeout
     */
    if(m_motor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast) != rev::CANError::kOK) {
      frc::SmartDashboard::PutString("Idle Mode", "Error");
    }

    /**
     * Similarly, parameters will have a Get method which allows you to retrieve their values
     * from the controller
     */
    if(m_motor.GetIdleMode() == rev::CANSparkMax::IdleMode::kCoast) {
      frc::SmartDashboard::PutString("Idle Mode", "Coast");
    } else {
      frc::SmartDashboard::PutString("Idle Mode", "Brake");
    }

    // Set ramp rate to 0
    if(m_motor.SetOpenLoopRampRate(0) != rev::CANError::kOK) {
      frc::SmartDashboard::PutString("Ramp Rate", "Error");
    }

    // read back ramp rate value
    frc::SmartDashboard::PutNumber("Ramp Rate", m_motor.GetOpenLoopRampRate());
  }
  
  void TeleopPeriodic() {
    // Set motor output to joystick value
    m_motor.Set(m_stick.GetY());
    
    // periodically read voltage, temperature, and applied output and publish to SmartDashboard
    frc::SmartDashboard::PutNumber("Voltage", m_motor.GetBusVoltage());
    frc::SmartDashboard::PutNumber("Temperature", m_motor.GetMotorTemperature());
    frc::SmartDashboard::PutNumber("Output", m_motor.GetAppliedOutput());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif