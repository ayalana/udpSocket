//#include "..\shared\Device.h"
//#include "Server_.h"
//#include <thread>
#pragma once
class Modem : Device
{
/// <summary>
/// ctor that received type program  and type of device
/// and run process that get messages and if need-return them.....
/// </summary>
public:
	Modem(int device,int type) :Device(device, type) {
		std::thread t1(&Modem::getMessage, this);
		t1.detach();
	}
	//process that get messages and if need-return them.....
	void getMessage() {
		int port;
		if (this->Type == RECEIVER)
			port = MODEM_RECEIVER;
		else
			port = MODEM_TRANSMITTER;
		//send port
		Device::getMessage(port);
	}
};

