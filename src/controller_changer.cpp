#include "controller_changer.h"



ControllerChanger::ControllerChanger() 
{
    initControllerIndex();
}


ControllerChanger::~ControllerChanger()
{
    for (BaseController* bc : controllerList) {
        delete bc;
    }
    controllerList.clear();
}


void ControllerChanger::setup()
{
    initControllerIndex();
    for (BaseController* bc : controllerList) {
        bc->setup();
    }
}


void ControllerChanger::loop()
{
    if (controllerList.size() == 0) return;
    if (currentControllerIndex != nextControllerIndex) {
        if (0 <= currentControllerIndex) controllerList[currentControllerIndex]->end();
        controllerList[nextControllerIndex]->begin();
        currentControllerIndex = nextControllerIndex;
    }
    controllerList[currentControllerIndex]->loop();
}


bool ControllerChanger::changeController(int index) 
{
    if (0 <= index && index < controllerList.size()) {
        nextControllerIndex = index;
        return true;
    }
    return false;
}


void ControllerChanger::changeNextController() 
{
    if (controllerList.size() == 0) return;
    if (nextControllerIndex != currentControllerIndex) return;

    if (currentControllerIndex + 1 >= controllerList.size())
        nextControllerIndex = 0;
    else
        nextControllerIndex += 1;
}

    
void ControllerChanger::changePrevController()
{
    if (controllerList.size() == 0) return;
    if (nextControllerIndex != currentControllerIndex) return;

    if (currentControllerIndex - 1 < 0)
        nextControllerIndex = controllerList.size() - 1;
    else
        nextControllerIndex -= 1;
}
    

void ControllerChanger::addController(BaseController* bc) 
{
    bc->setJoyc(joyc);
    controllerList.push_back(bc);
}


void ControllerChanger::setJoyc(JoyC* j) 
{
    joyc = j;
}


void ControllerChanger::initControllerIndex()
{
    currentControllerIndex = -1;
    nextControllerIndex = 0;
}

