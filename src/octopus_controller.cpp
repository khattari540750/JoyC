#include "octopus_controller.h"



void OcutopusController::setup()
{
	setDestAddress(0x10, 0x06, 0x1c, 0x16, 0x6f, 0x44);
}


void OcutopusController::begin()
{
	// display init
	StickCP2.Display.setTextFont(1);
	StickCP2.Display.setTextSize(1);
  StickCP2.Display.setCursor(0, 0);
	StickCP2.Display.fillScreen(GREEN);
	StickCP2.Display.setTextColor(BLACK, GREEN);
    
	// begin esp-now connection
	if(beginConnection()) {
		Serial.println("add pair success");
    StickCP2.Display.println(" add pair success");
    StickCP2.Display.println();
    StickCP2.Display.println(" dest mac address:");
    StickCP2.Display.print("  ");
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
						 destAddress[0], destAddress[1], destAddress[2], 
           	 destAddress[3], destAddress[4], destAddress[5]);
    StickCP2.Display.println(macStr);
  } else {
  	Serial.println("Failed to add peer");
    StickCP2.Display.println(" Failed to add peer");
    return;
  }
    
  // set callback
  esp_now_register_recv_cb(this->onDataRecv);

	// joy stic
  joyc->setLEDColor(0x000000);
}


void OcutopusController::loop()
{
	if(esp_now_is_peer_exist(destAddress)) {
  	// send
		sendData.leftX = joyc->getX(0);
    sendData.leftY = joyc->getY(0);
    sendData.leftPress = joyc->getPress(0);
    sendData.rightX = joyc->getX(1);
    sendData.rightY = joyc->getY(1);
    sendData.rightPress = joyc->getPress(1);
    esp_now_send(destAddress, (uint8_t*)&sendData, sizeof(sendData));

		// recv
		StickCP2.Display.setTextFont(1);
		StickCP2.Display.setTextSize(2);
  	StickCP2.Display.setCursor(0, 50);
  	StickCP2.Display.printf(" accel: %u \n", recvData.accel);
  	StickCP2.Display.printf(" strL: %u \n", recvData.steeringL);
  	StickCP2.Display.printf(" strR: %u \n", recvData.steeringR);

    delay(5);
  }
}


void OcutopusController::end()
{
  // end esp-now connection
  endConnection();
    
  // remove callback
  esp_now_unregister_recv_cb();
}


void OcutopusController::onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) 
{
	if (len == sizeof(recvData)) {
		memcpy(&recvData, incomingData, sizeof(status_data));
	}
}

OcutopusController::status_data OcutopusController::recvData;