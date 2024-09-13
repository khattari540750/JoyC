#include "my_controller.h"


void MyController::setup()
{

}


void MyController::begin()
{
    // display init
    StickCP2.Display.setTextFont(1);
	StickCP2.Display.setTextSize(2);
	StickCP2.Display.fillScreen(WHITE);
  	StickCP2.Display.setTextColor(BLACK, WHITE);
}


void MyController::loop()
{
    StickCP2.update();

    StickCP2.Display.setCursor(0, 1);
    memset(info, '\0', sizeof(info));
    sprintf(info, "L X:  %u  ", joyc->getX(0));
    StickCP2.Display.println(info);
    memset(info, '\0', sizeof(info));
    sprintf(info, "L Y:  %u  ", joyc->getY(0));
    StickCP2.Display.println(info);
    memset(info, '\0', sizeof(info));
    sprintf(info, "L Ang:%u  ", joyc->getAngle(0));
    StickCP2.Display.println(info);
    memset(info, '\0', sizeof(info));
    sprintf(info, "L Btn:%u  ", joyc->getPress(0));
    StickCP2.Display.println(info);
    memset(info, '\0', sizeof(info));
    sprintf(info, "R X:  %u  ", joyc->getX(1));
    StickCP2.Display.println(info);
    memset(info, '\0', sizeof(info));
    sprintf(info, "R Y:  %u  ", joyc->getY(1));
    StickCP2.Display.println(info);
    memset(info, '\0', sizeof(info));
    sprintf(info, "R Ang:%u  ", joyc->getAngle(1));
    StickCP2.Display.println(info);
    memset(info, '\0', sizeof(info));
    sprintf(info, "R Btn:%u  ", joyc->getPress(1));
    StickCP2.Display.println(info);
    StickCP2.Display.println("");
    memset(info, '\0', sizeof(info));
    sprintf(info, "Bat:%u  ", StickCP2.Power.getBatteryLevel());
    StickCP2.Display.println(info);

    if (joyc->getPress(0) && joyc->getPress(1)) {  // If the buttons are all pressed. 如果按键都被按下
        joyc->setLEDColor(0x00ffe8);
    } else if (joyc->getPress(0)) {
        joyc->setLEDColor(0xff0000);
    } else if (joyc->getPress(1)) {
        joyc->setLEDColor(0x0000ff);
    } else {
        joyc->setLEDColor(0x00ff00);
    }
}


void MyController::end()
{
    joyc->setLEDColor(0x000000);
}