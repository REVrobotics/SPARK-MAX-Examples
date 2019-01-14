# SPARK-MAX-Examples
## Table of Contents
* [Installing libraries Java/C++](#installjc)
* [Building and Running Examples in Visual Studio](#buildrunvs)
* [Installing libraries LabVIEW](#installlv)
* [Running Examples in LabVIEW](#runlv)


<a name="installjc"></a>
## Installing libraries for Java/C++
Download the SPARK-MAX-roboRIO-SDK from RevRobotics.
* <a href="http://www.revrobotics.com/content/sw/max/sdk/SPARK-MAX-roboRIO-SDK-1.0.26.zip">Java API</a>
* <a href="http://www.revrobotics.com/content/sw/max/sdk/SPARK-MAX-roboRIO-SDK-1.0.26.zip">C++ API</a>

Extract the zipped archive to a location where you can find it. Within the extracted folder, there will be two folders title "maven" and "vendordeps".

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Extracted%20Folder.PNG "SPARK-MAX-roboRIO-SDK")

Copy and paste these folders into the location <b>C:\Users\Public\frc2019</b>. Go ahead and replace the files in the destination if you are prompted.

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Copy%20Location.PNG "Copy Location")

### Installing in Visual Studio
Once the archive containing the SPARK-MAX-roboRIO-SDK has been extracted to the correct location, it can be installed in Visual Studio.

Begin by creating a new project in the language of your choice or by opening an existing project. Press <b>ctrl + shift + p</b> to bring up the command pallette and select <b>WPILib: Manage Vendor Libraries</b>

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Manage%20Vendor%20Libraries.png "Manage Vendor Libraries")

Then select <b>Install new libraries (offline)</b>, check the box next to <b>RevRobotics</b> and select <b>OK</b>.

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Select%20Library.png "Select Library")

After a few moments SPARK MAX libraries will be available for you to use in your current project. This process will need to be repeated for each subsequent project that requires SPARK MAX libraries.

For Java all functions can be imported using `import com.revrobotics.*;`. Similarly, for C++ use `#include "rev/CANSparkMax.h`.

<a name="#buildrunvs"></a>
## Building and Running Examples in Visual Studio
After cloning this GitHub repository, Java and C++ examples can be opened in Visual Studio by going to <b>File->Open Folder...</b> and selecting the parent folder of the example you want to run.

By default, the Team Number is set to 0 in the .wpilib/wpilib_preferences.json file. Make sure to change this to the Team Number configured on your roboRIO by either editing this file directly or by pressing <b>ctrl + shift + p</b> and selecting <b>WPILib: Set Team Number.</b>

<a name = "installlv"></a>
## Installing libraries for LabVIEW
Download the SPARK MAX LabVIEW API from RevRobotics <a href="http://www.revrobotics.com/content/sw/max/labview/rev-spark-max_1.0.0-26_windows_x64.nipkg">here</a>.

Simply run the installer and follow the instructions on screen.

<a name = "runlv"></a>
## Running Examples in LabVIEW
Open LabVIEW and select <b>File->Open Project...</b>. Open the <b>.lvproj</b> file in the top directory of the example you wish to run.

By default the IP address of the roboRIO is set to 172.22.11.2. This IP address will work if you are connecting to the roboRIO over USB, but if you are connected over ethernet or WIFI you will need to right click <b>Target</b>, select <b>Properties</b>, and configure the IP set for your roboRIO.

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Set%20IP.PNG "Set IP")

Run the program by opening <b>Robot Main.vi</b> a pressing the white arrow at the top of the window.

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Run.PNG "Run")
