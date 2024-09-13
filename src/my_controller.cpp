#include "my_controller.h"


void MyController::setup()
{

}


void MyController::begin()
{
    // display init
    StickCP2.Display.setTextFont(1);
	StickCP2.Display.setTextSize(2);
  	StickCP2.Display.setCursor(1, 1);
	StickCP2.Display.fillScreen(WHITE);
  	StickCP2.Display.setTextColor(BLACK,WHITE);
}


void MyController::loop()
{
    StickCP2.update();
    StickCP2.Display.setCursor(0, 0);
    sprintf(info, "leftX: %d", joyc->x0);
    M5.Display.println(info);
    sprintf(info, "leftY: %d", joyc->y0);
    M5.Display.println(info);
}


void MyController::end()
{

}