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
	// serial
	Serial.begin(115200);

	// display
	M5.Display.setRotation(0);
	M5.Display.setTextFont(1);
	M5.Display.setTextSize(1);
  	M5.Display.setCursor(0, 0);
	M5.Display.fillScreen(BLACK);
  	M5.Display.setTextColor(WHITE);
	
	// M5 & StickCP2
	auto cfg = M5.config();
	StickCP2.begin(cfg);

	// esp_now
	WiFi.mode(WIFI_STA);
  	WiFi.disconnect();
	if (esp_now_init() == ESP_OK) {
    	Serial.println("ESPNow Init Success");
		M5.Display.println("ESPNow Init Success");
		Serial.println(WiFi.macAddress());
		M5.Display.println(WiFi.macAddress());
  	} else {
    	Serial.println("ESPNow Init Failed");
		M5.Display.println("ESPNow Init Failed");
		delay(3000);
		ESP.restart();
  	}

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