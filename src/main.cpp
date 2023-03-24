#include <RMTT_Libs.h>
// Create an object
RMTT_RGB tt_rgb;


// Main program start
void setup() {
	tt_rgb.Init();
}
void loop() {
	tt_rgb.SetRGB(0,0,255);
	delay(1000);
	tt_rgb.SetRGB(0,255,0);
	delay(1000);
}
