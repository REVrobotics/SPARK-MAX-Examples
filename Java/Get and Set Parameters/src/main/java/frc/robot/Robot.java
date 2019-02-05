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

import com.revrobotics.CANError;
import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMax.IdleMode;
import com.revrobotics.CANSparkMaxLowLevel.MotorType;

/**
 * This is a demo program showing the use of the RobotDrive class, specifically
 * it contains the code necessary to operate a robot with tank drive.
 */
public class Robot extends TimedRobot {
  private Joystick m_stick;
  private static final int deviceID = 1;
  private CANSparkMax m_motor;

  @Override
  public void robotInit() {
    /**
     * deviceID is the CAN ID of the SPARK MAX you are using.
     * Change to match your setup
     */
    m_motor = new CANSparkMax(deviceID, MotorType.kBrushless);

    /**
     * The restoreFactoryDefaults method can be used to reset the configuration parameters
     * in the SPARK MAX to their factory default state. If no argument is passed, these
     * parameters will not persist between power cycles
     */
    m_motor.restoreFactoryDefaults();

    /**
     * Parameters can be set by calling the appropriate Set method on the CANSparkMax object
     * whose properties you want to change
     * 
     * Set methods will return one of three CANError values which will let you know if the 
     * parameter was successfully set:
     *  CANError.kOk
     *  CANError.kError
     *  CANError.kTimeout
     */
    if(m_motor.setIdleMode(IdleMode.kCoast) != CANError.kOK){
      SmartDashboard.putString("Idle Mode", "Error");
    }

    /**
     * Similarly, parameters will have a Get method which allows you to retrieve their values
     * from the controller
     */
    if(m_motor.getIdleMode() == IdleMode.kCoast) {
      SmartDashboard.putString("Idle Mode", "Coast");
    } else {
      SmartDashboard.putString("Idle Mode", "Brake");
    }

    // Set ramp rate to 0
    if(m_motor.setOpenLoopRampRate(0) != CANError.kOK) {
      SmartDashboard.putString("Ramp Rate", "Error");
    }

    // read back ramp rate value
    SmartDashboard.putNumber("Ramp Rate", m_motor.getOpenLoopRampRate());

    m_stick = new Joystick(0);
  }

  @Override
  public void teleopPeriodic() {
    // Set motor output to joystick value
    m_motor.set(m_stick.getY());
    
    // periodically read voltage, temperature, and applied output and publish to SmartDashboard
    SmartDashboard.putNumber("Voltage", m_motor.getBusVoltage());
    SmartDashboard.putNumber("Temperature", m_motor.getMotorTemperature());
    SmartDashboard.putNumber("Output", m_motor.getAppliedOutput());
  }
}
