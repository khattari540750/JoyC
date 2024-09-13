#ifndef BaseController_h
#define BaseController_h



#include <esp_now.h>
#include <M5StickCPlus2.h>
#include <Hat_JoyC.h>



class BaseController
{
protected:
    typedef struct controller_data 
    {
        uint8_t rightX;         // 0 ~ 200
        uint8_t rightY;         // 0 ~ 200
        uint16_t rightAngle;    // 
        uint16_t rightDistance; //
        uint8_t rightPress;     // 0 or 1
        uint8_t leftX;          // 0 ~ 200
        uint8_t leftY;          // 0 ~ 200
        uint16_t leftAngle;     //
        uint16_t leftDistance;  //
        uint8_t leftPress;      // 0 or 1
    } controller_data;

    typedef struct controller_data_lite 
    {
        uint8_t rightX;         // 0 ~ 200
        uint8_t rightY;         // 0 ~ 200
        uint8_t rightPress;     // 0 or 1
        uint8_t leftX;          // 0 ~ 200
        uint8_t leftY;          // 0 ~ 200
        uint8_t leftPress;      // 0 or 1
    } controller_data_lite;

protected:
    uint8_t destAddress[6];
    JoyC* joyc;

public:
    BaseController() {};
    virtual ~BaseController() {};
    
public:
    virtual void setup(){};
    virtual void begin(){};
    virtual void loop(){};
    virtual void end(){};

public:
    void setJoyc(JoyC* j) { this->joyc = j; };

protected:
    void setDestAddress(uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5)
    {
        destAddress[0] = a0;
        destAddress[1] = a1;
        destAddress[2] = a2;
        destAddress[3] = a3;
        destAddress[4] = a4;
        destAddress[5] = a5;
    };

    bool beginConnection()
    {
        esp_now_peer_info_t peerInfo;
        memset(&peerInfo, 0, sizeof(peerInfo));
        memcpy(peerInfo.peer_addr, destAddress, 6);
        peerInfo.encrypt = false;
        if (esp_now_add_peer(&peerInfo) != ESP_OK) {
            return false;
        }
        return true;
    };

    void endConnection()
    {
        if(esp_now_is_peer_exist(destAddress)) {
            esp_now_del_peer(destAddress);
        }
    };
};



#endif