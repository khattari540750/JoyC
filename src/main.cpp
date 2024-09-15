#include <M5StickCPlus2.h>
#include <Hat_JoyC.h>
#include <esp_now.h>
#include <WiFi.h>
#include "controller_changer.h"
#include "my_controller.h"
#include "octopus_controller.h"



JoyC joyc;
ControllerChanger controllerChanger;



void setup()
{
	// serial
	Serial.begin(BAUD_RATE);

	// display
	StickCP2.Display.setRotation(0);
	StickCP2.Display.setTextFont(1);
	StickCP2.Display.setTextSize(1);
  	StickCP2.Display.setCursor(0, 0);
	StickCP2.Display.fillScreen(BLACK);
  	StickCP2.Display.setTextColor(WHITE);
	
	// M5 & StickCP2
	auto cfg = M5.config();
	StickCP2.begin(cfg);

	// esp_now
	WiFi.mode(WIFI_STA);
  	WiFi.disconnect();
	if (esp_now_init() == ESP_OK) {
    	Serial.println("ESPNow Init Success");
		StickCP2.Display.println("ESPNow Init Success");
		Serial.println(WiFi.macAddress());
		StickCP2.Display.println(WiFi.macAddress());
  	} else {
    	Serial.println("ESPNow Init Failed");
		StickCP2.Display.println("ESPNow Init Failed");
		delay(3000);
		ESP.restart();
  	}
	delay(3000);

	// joyc
	joyc.begin();
	controllerChanger.setJoyc(&joyc);

	// add controllers
	controllerChanger.addController(new MyController());
	controllerChanger.addController(new OcutopusController());

	// changer setup
	controllerChanger.setup();
}


void loop()
{ 
	StickCP2.update();
	joyc.update();
	if ( M5.BtnA.wasReleased() ) {
    	controllerChanger.changeNextController();
  	}
	controllerChanger.loop();
}