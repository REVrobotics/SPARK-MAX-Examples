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
import com.revrobotics.CANDigitalInput.LimitSwitchPolarity;
import com.revrobotics.CANSparkMaxLowLevel.MotorType;

public class Robot extends TimedRobot {
  private Joystick m_stick;
  private static final int deviceID = 1;
  private CANSparkMax m_motor;
  private CANDigitalInput m_forwardLimit;
  private CANDigitalInput m_reverseLimit;

  public String kEnable;
  public String kDisable;

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
     * A CANDigitalInput object is constructed using the getForwardLimitSwitch() or
     * getReverseLimitSwitch() method on an existing CANSparkMax object, depending
     * on which direction you would like to limit
     * 
     * Limit switches can be configured to one of two polarities:
     *  com.revrobotics.CANDigitalInput.LimitSwitchPolarity.kNormallyOpen
     *  com.revrobotics.CANDigitalInput.LimitSwitchPolarity.kNormallyClosed
     */
    m_forwardLimit = m_motor.getForwardLimitSwitch(LimitSwitchPolarity.kNormallyClosed);
    m_reverseLimit = m_motor.getReverseLimitSwitch(LimitSwitchPolarity.kNormallyClosed);

    m_stick = new Joystick(0);

    /**
     * Limit switches are enabled by default when the are intialized. They can be disabled
     * by calling enableLimitSwitch(false) on a CANDigitalInput object
     * 
     * Limit switches can be reenabled by calling enableLimitSwitch(true)
     * 
     * The isLimitSwitchEnabled() method can be used to check if the limit switch is enabled
     */
    m_forwardLimit.enableLimitSwitch(false);
    m_reverseLimit.enableLimitSwitch(false);
    SmartDashboard.putBoolean("Forward Limit Enabled", m_forwardLimit.isLimitSwitchEnabled());
    SmartDashboard.putBoolean("Reverse Limit Enabled", m_reverseLimit.isLimitSwitchEnabled());
  }

  @Override
  public void teleopPeriodic() {
    m_motor.set(m_stick.getY());

    // enable/disable limit switches based on value read from SmartDashboard
    m_forwardLimit.enableLimitSwitch(SmartDashboard.getBoolean("Forward Limit Enabled", false));
    m_reverseLimit.enableLimitSwitch(SmartDashboard.getBoolean("Reverse Limit Enabled", false));

    /**
     * The get() method can be used on a CANDigitalInput object to read the state of the switch.
     * 
     * In this example, the polarity of the switches are set to normally closed. In this case,
     * get() will return true if the switch is pressed. It will also return true if you do not 
     * have a switch connected. get() will return false when the switch is released.
     */
    SmartDashboard.putBoolean("Forward Limit Switch", m_forwardLimit.get());
    SmartDashboard.putBoolean("Reverse Limit Switch", m_reverseLimit.get());
  }
}
