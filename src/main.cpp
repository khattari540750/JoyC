#include <M5StickCPlus2.h>
#include <Hat_JoyC.h>
#include <esp_now.h>
#include <WiFi.h>
#include "controller_changer.h"
#include "octopus_controller.h"



JoyC joyc;
ControllerChanger controllerChanger;



void setup()
{
	// M5 & StickCP2
	auto cfg = M5.config();
	StickCP2.begin(cfg);

	// esp_now
	WiFi.mode(WIFI_STA);
  	WiFi.disconnect();

	// joyc
	joyc.begin();
	controllerChanger.setJoyc(&joyc);

	// add
	controllerChanger.addController(new OcutopusController());
	controllerChanger.setup();
}


void loop()
{ 
	StickCP2.update();
	joyc.update();
	controllerChanger.loop();
}