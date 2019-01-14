# SPARK-MAX-Examples
## Table of Contents
* [Installing libraries Java/C++](#installjc)
* [Installing libraries LabVIEW](#installlv)


<a name="installjc"></a>
## Installing libraries for Java/C++
Download the SPARK-MAX-roboRIO-SDK from RevRobotics.
* <a href="http://www.revrobotics.com/content/sw/max/sdk/SPARK-MAX-roboRIO-SDK-1.0.26.zip">Java API</a>
* <a href="http://www.revrobotics.com/content/sw/max/sdk/SPARK-MAX-roboRIO-SDK-1.0.26.zip">C++ API</a>

Extract the zipped archive to a location where you can find it. Within the extracted folder, there will be two folders title "maven" and "vendordeps".

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Extracted%20Folder.PNG "SPARK-MAX-roboRIO-SDK")


### Windows
Copy and paste these folders into the location <b>C:\Users\Public\frc2019</b>. Go ahead and replace the files in the destination if you are prompted.

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Copy%20Location.PNG "Copy Location")


### MAC and Linux
TODO

### Installing in Visual Studio
Once the archive containing the SPARK-MAX-roboRIO-SDK has been extracted to the correct location, it can be installed in Visual Studio.

Begin by creating a new project in the language of your choice or by opening an existing project. Press <b>ctrl + shift + p</b> to bring up the command pallette and select <b>WPILib: Manage Vendor Libraries</b>

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Manage%20Vendor%20Libraries.png "Manage Vendor Libraries")

Then select <b>Install new libraries (offline)</b>, check the box next to <b>RevRobotics</b> and select <b>OK</b>.

![alt text](https://github.com/REVrobotics/SPARK-MAX-Examples/blob/master/images/Select%20Library.png "Select Library")

After a few moments SPARK MAX libraries will be available for you to use in your current project. This process will need to be repeated for each subsequent project that requires SPARK MAX libraries.

For Java all functions can be imported using `import com.revrobotics.*;`. Similarly, for C++ use `#include "rev/CANSparkMax.h`.

<a name = "installlv"></a>
## Installing libraries for LabVIEW
content
