#ifndef BaseController_h
#define BaseController_h



#include <esp_now.h>
#include <M5StickCPlus2.h>
#include <Hat_JoyC.h>



class BaseController 
{
protected:
    uint8_t destAddress[6];
    JoyC* joyc;
    
public:
    virtual void setup(){};
    virtual void begin(){};
    virtual void loop(){};
    virtual void end(){};

public:
    void setJoyc(JoyC* j) { this->joyc = j; };
};



#endif