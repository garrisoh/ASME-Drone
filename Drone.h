#ifndef DRONE_H
#define DRONE_H

#include <cstdio>

class Drone
{
private:
	FILE* _controlPipe;	/// File for drone control
	FILE* _ffplayPipe;	/// File for video feed
	
public:
	Drone();
	~Drone();
	
	void takeoff();
	void land();
	
	void move(float pitch, float roll, float yawRate, float vertSpeed);
	
	void hover();
	
	void emergencyStop();
	void resetEmergencyStop();
	
	void videoEnable(bool truthiness);

private:
	void sendCommand(const char* command);

};


Drone* getDrone();


#endif
