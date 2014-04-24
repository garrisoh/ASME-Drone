#include "Drone.h"

#include <cstdlib>
#include <string>
#include <sstream>


Drone::Drone()
{
	_controlPipe = popen("node ./repl.js", "w");
}
Drone::~Drone()
{
	// close streams
	videoEnable(false);
	pclose(_controlPipe);
}

void Drone::takeoff()
{
	sendCommand("takeoff()\n");
}
void Drone::land()
{
	sendCommand("land()\n");
}

void Drone::move(float pitch, float roll, float yawRate, float vertSpeed)
{
	std::stringstream stream;
	stream << "front(" << pitch << ")\n";
	stream << "left(" << roll << ")\n";
	stream << "clockwise(" << yawRate << ")\n";
	stream << "up(" << vertSpeed << ")\n";
	sendCommand(stream.str().c_str());
}

void Drone::hover()
{
	sendCommand("stop()\n");
}

void Drone::emergencyStop()
{
	sendCommand("createUdpControl().ref({fly: false, emergency: true})\n");
}

void Drone::resetEmergencyStop()
{
	sendCommand("disableEmergency()\n");
}

void Drone::videoEnable(bool truthiness)
{
	if(truthiness)
		_ffplayPipe = popen("ffplay tcp://192.168.1.1:5555", "r");
	else
		pclose(_ffplayPipe);
}

void Drone::sendCommand(const char* command)
{
	fwrite(command, sizeof(char), sizeof(command), _controlPipe);
}



Drone* getDrone()
{
	static Drone* drone = new Drone();
	return drone;
}

