#ifndef OcutopusController_h
#define OcutopusController_h



#include "base_controller.h"



class OcutopusController : public BaseController
{
private:
	typedef struct status_data
	{
		int8_t accel;
  	uint8_t steeringR;
  	uint8_t steeringL; 
	} status_data;

public:
  void setup();
  void begin();
  void loop();
  void end();

private:
	static void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);

private:
	controller_data_lite sendData;
	static status_data recvData;
};



#endif