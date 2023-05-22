#include <RMTT_Libs.h>
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

void curveCallback(char *cmd, String res)
{
	char msg[100];
	sprintf(msg, "The command was: %s\nRes: %s", cmd, res.c_str());
	Serial.println(String(msg));

	char *status = strstr(res.c_str(), "ok");
	if (status != NULL)
	{
		tt_rgb.SetRGB(0, 255, 0);
	}
	else
	{
		tt_rgb.SetRGB(255, 0, 0);
	}
}

// Main program start
// void setup()
// {
// 	tt_rgb.Init();
// 	tt_rgb.SetRGB(250, 0, 0);
// 	Serial.begin(115200);
// 	Serial1.begin(1000000, SERIAL_8N1, 23, 18);
// 	pinMode(5, OUTPUT);
// 	pinMode(12, INPUT | PULLUP);
// }
// void loop()
// {
// 	digitalWrite(5, LOW);
// 	tt_rgb.SetRGB(0, 250, 0);
// 	while (digitalRead(12) == 1)
// 	{
// 		delay(300);
// 	}
// 	digitalWrite(5, HIGH);
// 	delay(3000);
// 	tt_sdk.sdkOn(defaultCallback);
// 	tt_sdk.getBattery(defaultCallback);
// 	delay(1000);
// 	tt_rgb.SetRGB(0, 0, 250);
// 	delay(1000);
// }

void setup()
{
	tt_rgb.Init();
	tt_rgb.SetRGB(0, 0, 250);
	Serial.begin(115200);
	Serial1.begin(1000000, SERIAL_8N1, 23, 18);
}

void loop()
{
	tt_sdk.startUntilControl();
	delay(3000);
	// tt_sdk.getBattery(defaultCallback);
	tt_sdk.getBattery(defaultCallback);
	tt_sdk.takeOff(defaultCallback);
	delay(3000);
	// tt_sdk.forward(100, defaultCallback);
	// delay(5000);
	// tt_sdk.up(50, defaultCallback);
	// tt_rgb.SetRGB(255, 0, 0);
	tt_sdk.curve(50, 50, 50, 100, 100, 120, 20, curveCallback);
	delay(20000);
	tt_rgb.SetRGB(255, 255, 0);
	tt_sdk.land(defaultCallback);
}
