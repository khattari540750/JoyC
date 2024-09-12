#ifndef OcutopusController_h
#define OcutopusController_h



#include "base_controller.h"



class OcutopusController : public BaseController
{
public:
    void setup()
    {};


    void begin()
    {
    };


    void loop()
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
    };


    void end()
    {
        esp_now_unregister_send_cb();
        esp_now_unregister_recv_cb();
    };
};



#endif