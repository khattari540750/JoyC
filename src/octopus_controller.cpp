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
  	StickCP2.Display.setTextColor(BLACK);
    
    // begin esp-now connection
    if(beginConnection()) {
        Serial.println("Pair success");
        StickCP2.Display.println("Pair success");
    } else {
        Serial.println("Failed to add peer");
        StickCP2.Display.println("Failed to add peer");
        return;
    }
    
    // set callback
    esp_now_register_recv_cb(onDataRecv);

    // joy stic
    joyc->setLEDColor(0x000000);
}


void OcutopusController::loop()
{
    if(esp_now_is_peer_exist(destAddress)) {
        sendData.leftX = joyc->getX(0);
        sendData.leftY = joyc->getY(0);
        sendData.leftPress = joyc->getPress(0);
        sendData.rightX = joyc->getX(1);
        sendData.rightY = joyc->getY(1);
        sendData.rightPress = joyc->getPress(1);
        esp_now_send(destAddress, (uint8_t*)&sendData, sizeof(sendData));
    }
    delay(10);
}


void OcutopusController::end()
{
    // end esp-now connection
    endConnection();
    
    // remove callback
    esp_now_unregister_recv_cb();
}


void OcutopusController::onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) 
{
    char macStr[18];
    char msg[1];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.printf("Last Packet Recv from: %s\n", macStr);
    Serial.printf("Last Packet Recv Data(%d): ", data_len);
    for ( int i = 0 ; i < data_len ; i++ ) {
        msg[1] = data[i];
        Serial.print(msg[1]);
    }
    Serial.println("");
}