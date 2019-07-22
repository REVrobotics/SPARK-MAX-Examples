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
     * Soft Limits restrict the motion of the motor in a particular direction
     * at a particular point. Soft limits can be applied in only one direction, 
     * or both directions at the same time. 
     * 
     * If the soft limits are disabled and then re-enabled, they will retain
     * the last limits that they had for that particular direction.
     * 
     * The directions are rev::CANSparkMax::kForward and rev::CANSparkMax::kReverse
     */
    m_motor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
    m_motor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);

    m_motor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 15);
    m_motor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 0);
    
    frc::SmartDashboard::PutBoolean("Forward Soft Limit Enabled", 
                                    m_motor.IsSoftLimitEnabled(rev::CANSparkMax::SoftLimitDirection::kForward));
    frc::SmartDashboard::PutBoolean("Reveres Soft Limit Enabled", 
                                    m_motor.IsSoftLimitEnabled(rev::CANSparkMax::SoftLimitDirection::kReverse));
    frc::SmartDashboard::PutNumber("Forward Soft Limit", 
                                    m_motor.GetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward));
    frc::SmartDashboard::PutNumber("Reveres Soft Limit", 
                                    m_motor.GetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse));
  }

  void TeleopPeriodic() {
    m_motor.Set(m_stick.GetY());
    
    // Enable and disable the smart limits based on values read from the SmartDashboard
    m_motor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 
                         frc::SmartDashboard::GetBoolean("Forward Soft Limit Enabled", true));
    m_motor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 
                         frc::SmartDashboard::GetBoolean("Reverse Soft Limit Enabled", true));

    // Change the value of the limits based on values read from the SmartDashboard
    m_motor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 
                         frc::SmartDashboard::GetNumber("Forward SmaSoftrt Limit", 15));
    m_motor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 
                         frc::SmartDashboard::GetNumber("Reverse Soft Limit", 0));
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
