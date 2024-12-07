> [!WARNING]
> Starting 2025, this repository has been deprecated. SPARK MAX examples now exist in [REVLib-Examples](https://github.com/REVrobotics/REVLib-Examples).

# SPARK-MAX-Examples

## Table of Contents

* [Installing REVLib](#installing-revlib)
* [Running Examples in Visual Studio Code](#running-examples-in-visual-studio-code)
* [Running Examples in LabVIEW](#running-examples-in-labview)

## Installing REVLib

For information about installing and updating REVLib for use with the SPARK MAX Motor Controller, see our [documentation](https://docs.revrobotics.com/brushless/spark-max/revlib/).

## Running Examples in Visual Studio Code

After cloning this GitHub repository, Java and C++ examples can be opened in Visual Studio Code by going to **File > Open Folder...** and selecting the parent folder of the example you want to run.

By default, the Team Number is set to 0 in the `.wpilib/wpilib_preferences.json file`. Make sure to change this to the Team Number configured on your roboRIO by either editing this file directly or by pressing **Ctrl + Shift + P** and selecting **WPILib: Set Team Number**.

Run the program by right clicking `build.gradle` in file explorer of VS Code and selecting **Deploy Robot Code**.

## Running Examples in LabVIEW

Open LabVIEW and select **File > Open Project...**. Open the `.lvproj` file in the top directory of the example you wish to run.

By default, the IP address of the roboRIO is set to `172.22.11.2`. This IP address will work if you are connecting to the roboRIO over USB, but if you are connected over ethernet or WiFi you will need to right click **Target**, select **Properties**, and configure the IP set for your roboRIO, e.g. `roboRIO-<TEAM>-FRC.local`.

Run the program by opening `Robot Main.vi` and pressing the white arrow at the top of the window.
