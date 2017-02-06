# ASME Drone
This project was created by the Lafayette College ASME Motion Control Team.  It can be used to control the Parrot AR.Drone using the LEAP Motion controller.

## Prerequisites
The ffplay tool from the ffmpeg library is required to view the video feed from the drone.  Download and install ffmpeg from [ffmpeg.org](https://ffmpeg.org).  You will also need to have [Node.js](https://nodejs.org/en/) installed to run the code.

## Running the Project
To run the project, first clone or download the project files:

```
git clone https://github.com/garrisoh/ASME-Drone.git
```

After cloning the repo, make sure that the `launch.sh` file can be executed by modifying the file permissions:

```
chmod +x launch.sh
```

Make sure that your LEAP Motion controller has been setup properly and is plugged in.  Then run the launch script:

```
./launch.sh
```

The launch script will start the ffplay video feed and will run the droneControl.js file with Node.  The program will prompt you to hit enter/return to toggle takeoff/landing.  Pressing enter will cause the drone to takeoff and hover in place at its default height.  Once the drone is in the air, hitting enter again will cause it to land.

To control the drone with the LEAP Motion controller, first press enter to make the drone takeoff.  Then close your hand into a fist and place it about a foot above the LEAP Motion controller.  When you are ready to control the drone, open your hand (make sure your fingers are spread out slightly).  This will calibrate the system so the vertical speed of the drone is set to zero when your hand is at this initial height.  To control the forward/backward speed of the drone, tilt your hand slightly forward or backward.  The further you tilt your hand, the faster the drone will go.  To navigate left or right, tilt your hand left or right.  To go up or down, move your hand slightly above or below the initial height (when you first opened your hand).   To hover in place, close your hand.  When you are done controlling the drone, press enter to land.

## Command Line Control
This project also includes a script for controlling the drone over a networked connection.  You can control the drone with the command line by first running the following:

```
node ParrotServer.js
```

Then connect to the server via the command line using telnet:

```
telnet localhost 5678
```

To takeoff or land, enter one of the following commands:

```
takeoff
land
```

The takeoff command will cause the drone to takeoff and hover in place at a fixed height.  To move the drone, use one of the following commands, where <speed> is a number between 0.0 (no movement) and 1.0 (full speed):

```
forward <speed>
backward <speed>
left <speed>
right <speed>
clockwise <speed>
counterClockwise <speed>
```

Any motion commands will be set at the given speed until specified otherwise, so the following example will cause the drone to move diagonally:

```
forward 0.2
right 0.2
```

To stop motion in all directions and cause the drone to hover in place, use the following command:

```
hover
```
