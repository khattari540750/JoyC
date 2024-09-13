#ifndef ControllerChanger_h
#define ControllerChanger_h



#include <M5StickCPlus2.h>
#include <Hat_JoyC.h>
#include <base_controller.h>



class ControllerChanger
{
public:  // constructor & destructor
    ControllerChanger();
    ~ControllerChanger();

public: // basic functions
    void setup();
    void loop();

public: // change & add
    bool changeController(int index);
    void changeNextController();
    void changePrevController();
    void addController(BaseController* bc);

public: // set ptrs
    void setJoyc(JoyC* j);

private: // init function
    void initControllerIndex();

private: // system variables
    std::vector<BaseController*> controllerList;
    int8_t currentControllerIndex;
    int8_t nextControllerIndex;

private: // ptrs
    JoyC* joyc;
};



#endif