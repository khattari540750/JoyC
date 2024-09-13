#ifndef OcutopusController_h
#define OcutopusController_h



#include "base_controller.h"



class OcutopusController : public BaseController
{
private:
    typedef struct controller_data {
        uint8_t rightX;     // 0 ~ 200
        uint8_t rightY;     // 0 ~ 200
        uint8_t rightPress; // 0 or 1
        uint8_t leftX;      // 0 ~ 200
        uint8_t leftY;      // 0 ~ 200
        uint8_t leftPress;  // 0 or 1
    } controller_data;

public:
    void setup();
    void begin();
    void loop();
    void end();

private:
    static void onDataSend(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);

private:
    controller_data sendData;
};



#endif