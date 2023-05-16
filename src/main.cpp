#include <RMTT_Libs.h>
#include <Wire.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#define ADDRESS "192.168.10.1"
#define PORT 8080

// Create an object
RMTT_RGB tt_rgb;
RMTT_Protocol tt_sdk;
RMTT_TOF tt_sensor;

TaskHandle_t socketTaskHandle = NULL;
void socketTask(void *arg);

void defaultCallback(char *cmd, String res)
{
	char msg[100];
	sprintf(msg, "The command was: %s\nRes: %s", cmd, res.c_str());
	Serial.println(String(msg));
}	

// Main program start
void setup()
{
	tt_rgb.Init();
	tt_rgb.SetRGB(0, 0, 250);
	Serial.begin(115200);
	Serial1.begin(1000000, SERIAL_8N1, 23, 18);

	Wire.begin(27, 26);
	Wire.setClock(100000);
	tt_sensor.SetTimeout(500); // Set a single measurement timeout
	if (!tt_sensor.Init())
	{
		Serial.println("Failed to detect and initialize sensor!");
		while (1)
		{
		}
	}
}

void loop(){
}

void socketTask(void *arg)
{
}