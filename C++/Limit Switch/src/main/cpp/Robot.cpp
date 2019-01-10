/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "rev/CANSparkMax.h"
#include <iostream>
#include "rev/CANDigitalInput.h"

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
  frc::Joystick m_stick{0};

  rev::CANSparkMax m_motor{1, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANDigitalInput m_forwardLimitClosed = m_motor.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);
  rev::CANDigitalInput m_reverseLimitClosed = m_motor.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);
  rev::CANDigitalInput m_forwardLimitOpen = m_motor.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen);
  rev::CANDigitalInput m_reverseLimitOpen = m_motor.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen);

 public:
  void RobotInit() {
    //m_forwardLimitClosed.EnableLimitSwitch(false);
    //m_reverseLimitClosed.EnableLimitSwitch(false);
    //m_forwardLimitOpen.EnableLimitSwitch(false);
    //m_reverseLimitOpen.EnableLimitSwitch(false);

    m_polarityChooserForward.SetDefaultOption(kPolarityClosedForward, kPolarityClosedForward);
    m_polarityChooserForward.AddOption(kPolarityOpenForward, kPolarityOpenForward);
    frc::SmartDashboard::PutData("Polarity Modes Forward", &m_polarityChooserForward);

    m_enableChooserForward.SetDefaultOption(kEnableForward, kEnableForward);
    m_enableChooserForward.AddOption(kDisableForward, kDisableForward);
    frc::SmartDashboard::PutData("Enable Forward Limit", &m_enableChooserForward);

    m_polarityChooserReverse.SetDefaultOption(kPolarityClosedReverse, kPolarityClosedReverse);
    m_polarityChooserReverse.AddOption(kPolarityOpenReverse, kPolarityOpenReverse);
    frc::SmartDashboard::PutData("Polarity Modes Reverse", &m_polarityChooserReverse);

    m_enableChooserReverse.SetDefaultOption(kEnableReverse, kEnableReverse);
    m_enableChooserReverse.AddOption(kDisableReverse, kDisableReverse);
    frc::SmartDashboard::PutData("Enable Reverse Limit", &m_enableChooserReverse);
  }
  void TeleopPeriodic() {
    m_motor.Set(m_stick.GetY());
    static int prevSelectionForward = 0;
    static int prevSelectionReverse = 0;

    if(m_polarityChooserForward.GetSelected() == kPolarityOpenForward) {
      if(prevSelectionForward == 1) {
        m_forwardLimitOpen = m_motor.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen);
        prevSelectionForward = 0;
      }

      if(m_enableChooserForward.GetSelected() == kEnableForward) {
        m_forwardLimitOpen.EnableLimitSwitch(true);
      } else {
        m_forwardLimitOpen.EnableLimitSwitch(false);
      }
      
    } else {
      if(prevSelectionForward == 0) {
        m_forwardLimitClosed = m_motor.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);
        prevSelectionForward = 1;
      }

      if(m_enableChooserForward.GetSelected() == kEnableForward) {
        m_forwardLimitClosed.EnableLimitSwitch(true);
      } else {
        m_forwardLimitClosed.EnableLimitSwitch(false);
      }
    }

    if(m_polarityChooserReverse.GetSelected() == kPolarityOpenReverse) {
      if(prevSelectionReverse == 1) {
        m_reverseLimitOpen = m_motor.GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen);
        prevSelectionReverse = 0;
      }

      if(m_enableChooserReverse.GetSelected() == kEnableForward) {
        m_reverseLimitOpen.EnableLimitSwitch(true);
      } else {
        m_reverseLimitOpen.EnableLimitSwitch(false);
      }
      
    } else {
      if(prevSelectionReverse == 0) {
        m_reverseLimitClosed = m_motor.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);
        prevSelectionReverse = 1;
      }

      if(m_enableChooserReverse.GetSelected() == kEnableForward) {
        m_reverseLimitClosed.EnableLimitSwitch(true);
      } else {
        m_reverseLimitClosed.EnableLimitSwitch(false);
      }
    }
  }

  frc::SendableChooser<std::string> m_enableChooserForward;
  const std::string kEnableForward = "Enable";
  const std::string kDisableForward = "Disable";

  frc::SendableChooser<std::string> m_enableChooserReverse;
  const std::string kEnableReverse = "Enable";
  const std::string kDisableReverse = "Disable";

  frc::SendableChooser<std::string> m_polarityChooserForward;
  const std::string kPolarityOpenForward = "Normally Open";
  const std::string kPolarityClosedForward = "Normally Closed";

  frc::SendableChooser<std::string> m_polarityChooserReverse;
  const std::string kPolarityOpenReverse = "Normally Open";
  const std::string kPolarityClosedReverse = "Normally Closed";
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
