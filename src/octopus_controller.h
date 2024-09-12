#ifndef OcutopusController_h
#define OcutopusController_h



#include "base_controller.h"



class OcutopusController : public BaseController
{
public:
    void setup();
    void begin();
    void loop();
    void end();

private:
    static void onDataSend(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);
};



#endif