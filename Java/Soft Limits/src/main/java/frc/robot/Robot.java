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

import com.revrobotics.spark.SparkLowLevel.MotorType;
import com.revrobotics.spark.SparkMax;
import com.revrobotics.spark.SparkBase.PersistMode;
import com.revrobotics.spark.SparkBase.ResetMode;
import com.revrobotics.spark.config.SparkMaxConfig;
import com.revrobotics.spark.config.SparkBaseConfig.IdleMode;


public class Robot extends TimedRobot {
  private Joystick joystick;
  private static final int deviceID = 1;
  private static final double forwardLimitDefault = 15.0;
  private static final double reverseLimitDefault = -15.0;
  private SparkMax motor;
  private SparkMaxConfig motorConfig;
  @Override
  public void robotInit() {

    // Initialize SPARK MAX with CAN ID
    motor = new SparkMax(deviceID, MotorType.kBrushless);

    // Create the SPARK MAX Configurator to hold our desired changes
    motorConfig = new SparkMaxConfig();

    // Chain method calls to set soft limit values
    motorConfig.softLimit
      .forwardSoftLimit(forwardLimitDefault)
      .reverseSoftLimit(reverseLimitDefault)
      .forwardSoftLimitEnabled(true)
      .reverseSoftLimitEnabled(true);
      
    // Set idle mode to brake
    motorConfig.idleMode(IdleMode.kBrake);
    
    // Restore defaults and before setting our soft limit parameters and saving changes to eeprom 
    motor.configure(motorConfig, ResetMode.kResetSafeParameters, PersistMode.kPersistParameters);

    // Display current motor parameter values on smart dashboard
    SmartDashboard.putBoolean("Forward Soft Limit Enabled",
                              motor.configAccessor.softLimit.getForwardSoftLimitEnabled());
    SmartDashboard.putBoolean("Reverse Soft Limit Enabled",
                              motor.configAccessor.softLimit.getReverseSoftLimitEnabled());                          
    SmartDashboard.putNumber("Forward Soft Limit",
                              motor.configAccessor.softLimit.getForwardSoftLimit());
    SmartDashboard.putNumber("Reverse Soft Limit",
                              motor.configAccessor.softLimit.getReverseSoftLimit());
    SmartDashboard.putNumber("Current Position", motor.getEncoder().getPosition());
    joystick = new Joystick(0);
  }

  @Override
  public void teleopPeriodic() {
    motor.set(joystick.getY());

    // Refresh the soft limit configuration based on dashboard values
    motorConfig.softLimit
      .forwardSoftLimitEnabled(SmartDashboard.getBoolean("Forward Soft Limit Enabled", true))
      .reverseSoftLimitEnabled(SmartDashboard.getBoolean("Reverse Soft Limit Enabled", true))
      .forwardSoftLimit((float)SmartDashboard.getNumber("Forward Soft Limit", forwardLimitDefault))
      .reverseSoftLimit((float)SmartDashboard.getNumber("Reverse Soft Limit", reverseLimitDefault));

    // Only apply configuration changes to the motor
    motor.configure(motorConfig, ResetMode.kNoResetSafeParameters, PersistMode.kNoPersistParameters);

    // Display the current position of the motor 
    SmartDashboard.putNumber("Current Position", motor.getEncoder().getPosition());
  }
}
