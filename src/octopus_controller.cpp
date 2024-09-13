#include "octopus_controller.h"



void OcutopusController::setup()
{
    destAddress[0] = 0x3C;
    destAddress[1] = 0x61;
    destAddress[2] = 0x05;
    destAddress[3] = 0x0D;
    destAddress[4] = 0xB2;
    destAddress[5] = 0xB2;
}


void OcutopusController::begin()
{
    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, destAddress, 6);
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        M5.Display.println("Failed to add peer");
        return;
    }
    Serial.println("Pair success");
    M5.Display.println("Pair success");
    
    // set callback
    //esp_now_register_send_cb(onDataSend);
    //esp_now_register_recv_cb(onDataRecv);
}


void OcutopusController::loop()
{
    if (joyc->btn0 && joyc->btn1) {
        joyc->setLEDColor(0x00ffe8);
    } else if (joyc->btn0) {
        joyc->setLEDColor(0xff0000);
    } else if (joyc->btn1) {
        joyc->setLEDColor(0x0000ff);
    } else {
        joyc->setLEDColor(0x00ff00);
    }
    if(esp_now_is_peer_exist(destAddress)) {
        sendData.rightX = joyc->getX(0);
        sendData.rightY = joyc->getY(0);
        sendData.rightPress = joyc->getY(0);
        sendData.leftX = joyc->getX(1);
        sendData.leftY = joyc->getY(1);
        sendData.leftPress = joyc->getY(1);
        esp_now_send(destAddress, (uint8_t*)&sendData, sizeof(sendData));
    }
    sleep(10);
}


void OcutopusController::end()
{
    // delete peer
    if(esp_now_is_peer_exist(destAddress)) {
        esp_now_del_peer(destAddress);
    }
    
    // remove callback
    //esp_now_unregister_send_cb();
    //esp_now_unregister_recv_cb();
}


void OcutopusController::onDataSend(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print("Last Packet Sent to: ");
    Serial.println(macStr);
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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