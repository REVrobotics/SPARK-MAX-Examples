/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.TimedRobot;

import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMaxLowLevel.MotorType;

/**
 * This sample program shows how to control a motor using a joystick. In the
 * operator control part of the program, the joystick is read and the value is
 * written to the motor.
 *
 * <p>Joystick analog values range from -1 to 1 and speed controller inputs also
 * range from -1 to 1 making it easy to work together.
 */
public class Robot extends TimedRobot {
  private static final int leadDeviceID = 1;
  private static final int followDeviceID = 2;
  private static final int kJoystickPort = 0;

  private CANSparkMax m_leadMotor;
  private CANSparkMax m_followMotor;
  private Joystick m_joystick;

  @Override
  public void robotInit() {
    /**
     * SPARK MAX controllers are intialized over CAN by constructing a CANSparkMax object
     * 
     * The CAN ID, which can be configured using the SPARK MAX Client, is passed as the
     * first parameter
     * 
     * The motor type is passed as the second parameter. Motor type can either be:
     *  com.revrobotics.CANSparkMaxLowLevel.MotorType.kBrushless
     *  com.revrobotics.CANSparkMaxLowLevel.MotorType.kBrushed
     * 
     * The example below initializes two brushless motors with CAN IDs 1 and 2. Change
     * these parameters to match your setup
     */
    m_leadMotor = new CANSparkMax(leadDeviceID, MotorType.kBrushless);
    m_followMotor = new CANSparkMax(followDeviceID, MotorType.kBrushless);

    /**
     * The RestoreFactoryDefaults method can be used to reset the configuration parameters
     * in the SPARK MAX to their factory default state. If no argument is passed, these
     * parameters will not persist between power cycles
     */
    m_leadMotor.restoreFactoryDefaults();
    m_followMotor.restoreFactoryDefaults();

    /**
     * In CAN mode, one SPARK MAX can be configured to follow another. This is done by calling
     * the follow() method on the SPARK MAX you want to configure as a follower, and by passing
     * as a parameter the SPARK MAX you want to configure as a leader.
     */
    m_followMotor.follow(m_leadMotor);

    m_joystick = new Joystick(kJoystickPort);
  }

  @Override
  public void teleopPeriodic() {
    /**
     * m_followMotor will automatically follow whatever the applied output is on m_leadMotor.
     * 
     * Thus, set only needs to be called on m_leadMotor to control both of them
     */
    m_leadMotor.set(m_joystick.getY());
  }
}
