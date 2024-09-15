#ifndef MyController_h
#define MyController_h



#include "base_controller.h"
#include "WiFi.h"



class MyController : public BaseController
{
public:
    void setup();
    void begin();
    void loop();
    void end();

private:
    char info[25];
};



#endif