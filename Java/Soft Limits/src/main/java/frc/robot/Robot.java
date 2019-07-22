/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

import com.revrobotics.CANDigitalInput;
import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMaxLowLevel.MotorType;

public class Robot extends TimedRobot {
  private Joystick m_stick;
  private static final int deviceID = 1;
  private CANSparkMax m_motor;

  @Override
  public void robotInit() {
    // initialize SPARK MAX with CAN ID
    m_motor = new CANSparkMax(deviceID, MotorType.kBrushless);

    /**
     * The RestoreFactoryDefaults method can be used to reset the configuration parameters
     * in the SPARK MAX to their factory default state. If no argument is passed, these
     * parameters will not persist between power cycles
     */
    m_motor.restoreFactoryDefaults();

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
    m_motor.enableSoftLimit(CANSparkMax.SoftLimitDirection.kForward, true);
    m_motor.enableSoftLimit(CANSparkMax.SoftLimitDirection.kReverse, true);

    m_motor.setSoftLimit(CANSparkMax.SoftLimitDirection.kForward, 15);
    m_motor.setSoftLimit(CANSparkMax.SoftLimitDirection.kReverse, 0);

    SmartDashboard.putBoolean("Forward Soft Limit Enabled",
                              m_motor.isSoftLimitEnabled(CANSparkMax.SoftLimitDirection.kForward));
    SmartDashboard.putBoolean("Reverse Soft Limit Enabled",
                              m_motor.isSoftLimitEnabled(CANSparkMax.SoftLimitDirection.kReverse));                          
    SmartDashboard.putNumber("Forward Soft Limit",
                              m_motor.getSoftLimit(CANSparkMax.SoftLimitDirection.kForward));
    SmartDashboard.putNumber("Forward Soft Limit",
                              m_motor.getSoftLimit(CANSparkMax.SoftLimitDirection.kReverse));

    m_stick = new Joystick(0);
  }

  @Override
  public void teleopPeriodic() {
    m_motor.set(m_stick.getY());

    m_motor.enableSoftLimit(CANSparkMax.SoftLimitDirection.kForward, 
                            SmartDashboard.getBoolean("Forward Soft Limit Enabled", true));
    m_motor.enableSoftLimit(CANSparkMax.SoftLimitDirection.kReverse, 
                            SmartDashboard.getBoolean("Reverse Soft Limit Enabled", true));
    m_motor.setSoftLimit(CANSparkMax.SoftLimitDirection.kForward, 
                         (float)SmartDashboard.getNumber("Forward Soft Limit", 15));
    m_motor.setSoftLimit(CANSparkMax.SoftLimitDirection.kReverse,
                         (float)SmartDashboard.getNumber("Reverse Soft Limit", 0));
  }
}
