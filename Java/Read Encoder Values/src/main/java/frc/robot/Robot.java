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

import com.revrobotics.CANSparkMax;
import com.revrobotics.CANEncoder;
import com.revrobotics.CANSparkMaxLowLevel.MotorType;

/**
 * This is a demo program showing the use of the RobotDrive class, specifically
 * it contains the code necessary to operate a robot with tank drive.
 */
public class Robot extends TimedRobot {
  private Joystick m_stick;
  private static final int deviceID = 1;
  private CANSparkMax m_motor;
  private CANEncoder m_encoder;

  @Override
  public void robotInit() {
    // initialize SPARK MAX
    m_motor = new CANSparkMax(deviceID, MotorType.kBrushless);

    /**
    * In order to read encoder values an encoder object is created using the 
    * getEncoder() method from an existing CANSparkMax object
    */
    m_encoder = m_motor.getEncoder();

    m_stick = new Joystick(0);
  }

  @Override
  public void teleopPeriodic() {
    // set the motor output based on jostick position
    m_motor.set(m_stick.getY());

    /**
     * Encoder position is read from a CANEncoder object by calling the
     * GetPosition() method.
     * 
     * GetPosition() returns the position of the encoder in units of revolutions
     */
    SmartDashboard.putNumber("Encoder Position", m_encoder.getPosition());

    /**
     * Encoder velocity is read from a CANEncoder object by calling the
     * GetVelocity() method.
     * 
     * GetVelocity() returns the velocity of the encoder in units of RPM
     */
    SmartDashboard.putNumber("Encoder Velocity", m_encoder.getVelocity());
  }
}
