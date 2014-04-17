#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>

int main(int argc, const char **argv)
{
	// call command line tools
	//FILE *ffplay = popen("ffplay tcp://192.168.1.1:5555", "r");
	FILE *p = popen("node ./repl.js", "w");

	// commmands
	char str[] = "animateLeds('fire', 2, 10.0)\n";
	
	// write commands
	fwrite(str, sizeof(char), sizeof(str), p); 
	//std::string emergency;
	//std::cin >> emergency;

	//char str3[] = "takeoff()\n";
	//fwrite(str3, sizeof(char), sizeof(str3), p);

	/*if (emergency == "y") {
		char str2[] = "createUdpControl().ref({fly: false, emergency: true})\n";
		fwrite(str2, sizeof(char), sizeof(str2), p);
	}*/

	//char str4[] = "land()\n";
	//fwrite(str4, sizeof(char), sizeof(str4), p);

	// close streams
	pclose(p);
	//pclose(ffplay);
	return 0;
}
