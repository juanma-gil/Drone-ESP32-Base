#include <RMTT_Libs.h>
#include <WiFi.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

// Create an object
RMTT_RGB tt_rgb;
RMTT_Protocol tt_sdk;

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
	tt_rgb.SetRGB(250, 0, 0);
	Serial.begin(115200);
	Serial1.begin(1000000, SERIAL_8N1, 23, 18);
	 
 }
void loop()
{
	tt_rgb.SetRGB(0, 250, 0);
	
	tt_sdk.startUntilControl(); // Esta funcion ejecuta el comando "command" que inicializa el sdk
	//tt_sdk.sdkOn(defaultCallback);
	delay(1000);
	tt_sdk.motorOn(defaultCallback);
	delay(1000);
	tt_sdk.getBattery(defaultCallback);
	delay(1000);
	tt_sdk.getWiFi(defaultCallback);
	tt_sdk.streamOn(defaultCallback); 
	delay(1000);
	tt_sdk.setResolution((char *)"low", defaultCallback);
	delay(1000); 
	tt_sdk.sendCmd((char *)"motoroff", defaultCallback); //Si se quiere enviar alguna función usando los strings
	delay(1000);
	tt_sdk.streamOff(defaultCallback);
	tt_rgb.SetRGB(0, 0, 250);
	delay(5000);
}