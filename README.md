# SPARK-MAX-Examples
## Table of Contents
* [Installing libraries Java/C++](#installjc)
* [Installing libraries LabVIEW](#installlv)


<a name="installjc"></a>
## Installing libraries for Java/C++
Download the SPARK-MAX-roboRIO-SDK from RevRobotics <a href="">here</a>.(TODO: ADD LINK)
Extract the zipped archive to a location where you can find it. Within the extracted folder, there will be two folders title "maven" and "vendordeps".

### Windows
Copy and paste these folders into the location C:\Users\Public\frc2019. Go ahead and replace the files in the destination if you are prompted.

### MAC and Linux
TODO

### Installing in Visual Studio
Once the archive containing the SPARK-MAX-roboRIO-SDK has been extracted to the correct location, it can be installed in Visual Studio.

Begin by creating a new project in the language of your choice or by opening an existing project. Press <b>ctrl + shift + p</b> to bring up the command pallette and select <b>WPILib: Manage Vendor Libraries</b>

Then select <b>Install new libraries (offline)</b>, check the box next to <b>RevRobotics</b> and select <b>OK</b>.

After a few moments SPARK MAX libraries will be available for you to use in your current project. This process will need to be repeated for each subsequent project that requires SPARK MAX libraries.

<a name = "installlv"></a>
## Installing libraries for LabVIEW
content
