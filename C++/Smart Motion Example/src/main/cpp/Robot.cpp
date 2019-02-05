/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include "rev/CANSparkMax.h"

/**
 * Before Running:
 * Open shuffleBoard, select File->Load Layout and select the 
 * shuffleboard.json that is in the root directory of this example
 * 
 * Tuning Instructions:
 * 0) Before using this function, you should understand from your specific 
 * mechanism the max acceleration and the max velocity. You can obtain these 
 * either by design constraints, or running in open loop mode and 
 * calculating these values.
 * 
 * 1) Set the 'Smart Motion/Velocity' switch to 'Velocity'
 * 
 * 2) Tune the mechanism as you would a Velocity PID loop until the 
 * mechanism is controlled fairly well. In this mode the 'Set Velocity' slider 
 * controls the Velocity of the mechanism.
 * 
 * 3) Configure the smart motion parameters, and set the 'Mode' switch to 
 * 'Smart Motion'. In this mode, the 'Set Position' text box controls the Position 
 * of the mechansim. For initial tests it is recommended to keep the max velocity 
 * and max acceleration lower than the max value, and slowly increase these to 
 * the desired level.
 * 
 * 4) Test the mechanism by setting the position within the allowable range of 
 * the mechanism, and slowly increase limits until the system is working 
 * as intended.
 */
class Robot : public frc::TimedRobot {
  static const int deviceID = 1;
  rev::CANSparkMax m_motor{deviceID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANPIDController m_pidController = m_motor.GetPIDController();
  rev::CANEncoder m_encoder = m_motor.GetEncoder();

  // default PID coefficients
  double kP = 5e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0, kMaxOutput = 1, kMinOutput = -1;

  // default smart motion coefficients
  double kMaxVel = 2000, kMinVel = 0, kMaxAcc = 1500, kAllErr = 0;

  // motor max RPM
  const double MaxRPM = 5700;

  frc::Joystick m_stick{0};

 public:
  void RobotInit() {
    // set PID coefficients
    m_pidController.SetP(kP);
    m_pidController.SetI(kI);
    m_pidController.SetD(kD);
    m_pidController.SetIZone(kIz);
    m_pidController.SetFF(kFF);
    m_pidController.SetOutputRange(kMinOutput, kMaxOutput);

    /**
     * Smart Motion coefficients are set on a CANPIDController object
     * 
     * - setSmartMotionMaxVelocity() will limit the velocity in RPM of
     * the pid controller in Smart Motion mode
     * - setSmartMotionMinOutputVelocity() will put a lower bound in
     * RPM of the pid controller in Smart Motion mode
     * - setSmartMotionMaxAccel() will limit the acceleration in RPM^2
     * of the pid controller in Smart Motion mode
     * - setSmartMotionAllowedClosedLoopError() will set the max allowed
     * error for the pid controller in Smart Motion mode
     */
    m_pidController.SetSmartMotionMaxVelocity(kMaxVel);
    m_pidController.SetSmartMotionMinOutputVelocity(kMinVel);
    m_pidController.SetSmartMotionMaxAccel(kMaxAcc);
    m_pidController.SetSmartMotionAllowedClosedLoopError(kAllErr);

    // display PID coefficients on SmartDashboard
    frc::SmartDashboard::PutNumber("P Gain", kP);
    frc::SmartDashboard::PutNumber("I Gain", kI);
    frc::SmartDashboard::PutNumber("D Gain", kD);
    frc::SmartDashboard::PutNumber("I Zone", kIz);
    frc::SmartDashboard::PutNumber("Feed Forward", kFF);
    frc::SmartDashboard::PutNumber("Max Output", kMaxOutput);
    frc::SmartDashboard::PutNumber("Min Output", kMinOutput);

    // display Smart Motion coefficients
    frc::SmartDashboard::PutNumber("Max Velocity", kMaxVel);
    frc::SmartDashboard::PutNumber("Min Velocity", kMinVel);
    frc::SmartDashboard::PutNumber("Max Acceleration", kMaxAcc);
    frc::SmartDashboard::PutNumber("Allowed Closed Loop Error", kAllErr);
    frc::SmartDashboard::PutNumber("Set Position", 0);
    frc::SmartDashboard::PutNumber("Set Velocity", 0);

    // button to toggle between velocity and smart motion modes
    frc::SmartDashboard::PutBoolean("Mode", true);
  }

  void TeleopPeriodic() {
    // read PID coefficients from SmartDashboard
    double p = frc::SmartDashboard::GetNumber("P Gain", 0);
    double i = frc::SmartDashboard::GetNumber("I Gain", 0);
    double d = frc::SmartDashboard::GetNumber("D Gain", 0);
    double iz = frc::SmartDashboard::GetNumber("I Zone", 0);
    double ff = frc::SmartDashboard::GetNumber("Feed Forward", 0);
    double max = frc::SmartDashboard::GetNumber("Max Output", 0);
    double min = frc::SmartDashboard::GetNumber("Min Output", 0);
    double maxV = frc::SmartDashboard::GetNumber("Max Velocity", 0);
    double minV = frc::SmartDashboard::GetNumber("Min Velocity", 0);
    double maxA = frc::SmartDashboard::GetNumber("Max Acceleration", 0);
    double allE = frc::SmartDashboard::GetNumber("Allowed Closed Loop Error", 0);

    // if PID coefficients on SmartDashboard have changed, write new values to controller
    if((p != kP))   { m_pidController.SetP(p); kP = p; }
    if((i != kI))   { m_pidController.SetI(i); kI = i; }
    if((d != kD))   { m_pidController.SetD(d); kD = d; }
    if((iz != kIz)) { m_pidController.SetIZone(iz); kIz = iz; }
    if((ff != kFF)) { m_pidController.SetFF(ff); kFF = ff; }
    if((max != kMaxOutput) || (min != kMinOutput)) { m_pidController.SetOutputRange(min, max); kMinOutput = min; kMaxOutput = max; }
    if((maxV != kMaxVel)) { m_pidController.SetSmartMotionMaxVelocity(maxV); kMaxVel = maxV; }
    if((minV != kMinVel)) { m_pidController.SetSmartMotionMaxVelocity(minV); kMinVel = minV; }
    if((maxA != kMaxAcc)) { m_pidController.SetSmartMotionMaxAccel(maxA); kMaxAcc = maxA; }
    if((allE != kAllErr)) { m_pidController.SetSmartMotionAllowedClosedLoopError(allE); allE = kAllErr; }

    double SetPoint, ProcessVariable;
    bool mode = frc::SmartDashboard::GetBoolean("Mode", false);
    if(mode) {
      SetPoint = frc::SmartDashboard::GetNumber("Set Velocity", 0);
      m_pidController.SetReference(SetPoint, rev::ControlType::kVelocity);
      ProcessVariable = m_encoder.GetVelocity();
    } else {
      SetPoint = frc::SmartDashboard::GetNumber("Set Position", 0);
      /**
       * As with other PID modes, Smart Motion is set by calling the
       * SetReference method on an existing pid object and setting
       * the control type to kSmartMotion
       */
      m_pidController.SetReference(SetPoint, rev::ControlType::kSmartMotion);
      ProcessVariable = m_encoder.GetPosition();
    }
    
    frc::SmartDashboard::PutNumber("Set Point", SetPoint);
    frc::SmartDashboard::PutNumber("Process Variable", ProcessVariable);
    frc::SmartDashboard::PutNumber("Output", m_motor.GetAppliedOutput());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
