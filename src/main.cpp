#include <RMTT_Libs.h>
#include <Wire.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

// Create an object
RMTT_RGB tt_rgb;
RMTT_Protocol tt_sdk;
RMTT_TOF tt_sensor;

TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t mainTaskHandle = NULL;
void sensor_task(void *arg);
void main_task(void *arg);
void defaultCallback(char *cmd, String res)
{
	char msg[100];
	sprintf(msg, "The command was: %s\nRes: %s", cmd, res.c_str());
	Serial.println(String(msg));
}
void mainTaskCallback(char *cmd, String res)
{
	xTaskCreateUniversal(sensor_task, "sensor_task", 8192, NULL, 1, &sensorTaskHandle, 0);
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
	tt_sdk.startUntilControl();
	delay(1000);
	tt_sdk.takeOff(mainTaskCallback);
}

void sensor_task(void *arg)
{
	while (tt_sensor.ReadRangeSingleMillimeters() > 300)
	{
		delay(10);
	}
	tt_rgb.SetRGB(250, 0, 0);
	tt_sdk.land(defaultCallback);
}