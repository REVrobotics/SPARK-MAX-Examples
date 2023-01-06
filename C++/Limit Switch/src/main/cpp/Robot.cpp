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
  // initialize SPARK MAX with CAN ID
  static const int deviceID = 1;
  rev::CANSparkMax m_motor{deviceID, rev::CANSparkMax::MotorType::kBrushless};

  /**
   * A SparkMaxLimitSwitch object is constructed using the GetForwardLimitSwitch() or
   * GetReverseLimitSwitch() method on an existing CANSparkMax object, depending
   * on which direction you would like to limit
   * 
   * Limit switches can be configured to one of two polarities:
   *  rev::SparkMaxLimitSwitch::Type::kNormallyOpen
   *  rev::SparkMaxLimitSwitch::Type::kNormallyClosed
   */
  rev::SparkMaxLimitSwitch m_forwardLimit = m_motor.GetForwardLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyClosed);
  rev::SparkMaxLimitSwitch m_reverseLimit = m_motor.GetReverseLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyClosed);

  frc::Joystick m_stick{0};

 public:
  void RobotInit() {
    /**
     * Limit switches are enabled by default when the are intialized. They can be disabled
     * by calling enableLimitSwitch(false) on a SparkMaxLimitSwitch object
     * 
     * Limit switches can be reenabled by calling enableLimitSwitch(true)
     * 
     * The isLimitSwitchEnabled() method can be used to check if the limit switch is enabled
     */
    m_forwardLimit.EnableLimitSwitch(false);
    m_reverseLimit.EnableLimitSwitch(false);
    frc::SmartDashboard::PutBoolean("Forward Limit Enabled", m_forwardLimit.IsLimitSwitchEnabled());
    frc::SmartDashboard::PutBoolean("Reverse Limit Enabled", m_reverseLimit.IsLimitSwitchEnabled());
  }
  void TeleopPeriodic() {
    m_motor.Set(m_stick.GetY());

    // enable/disable limit switches based on value read from SmartDashboard
    m_forwardLimit.EnableLimitSwitch(frc::SmartDashboard::GetBoolean("Forward Limit Enabled", false));
    m_reverseLimit.EnableLimitSwitch(frc::SmartDashboard::GetBoolean("Reverse Limit Enabled", false));

    /**
     * The Get() method can be used on a SparkMaxLimitSwitch object to read the state of the switch.
     * 
     * In this example, the polarity of the switches are set to normally closed. In this case,
     * Get() will return true if the switch is pressed. It will also return true if you do not 
     * have a switch connected. Get() will return false when the switch is released.
     */
    frc::SmartDashboard::PutBoolean("Forward Limit Switch", m_forwardLimit.Get());
    frc::SmartDashboard::PutBoolean("Reverse Limit Switch", m_forwardLimit.Get());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
