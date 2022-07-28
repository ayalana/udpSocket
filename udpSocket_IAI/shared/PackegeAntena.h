#include "..\..\shared\Device.h"
#pragma once
class Antena: Device
{
/// <summary>
/// ctor that received type program  and type of device
/// and run process that get messages and if need-return them.....
/// </summary>
public:
	Antena(int device, int type) : Device(device, type) {
		std::thread t1(&Antena::getMessage, this);
		t1.detach();
	}
	//process that get messagesand if need - return them.....
	void getMessage() {
		int port;
		if (this->Type == RECEIVER)
			port = ANTENA_RECEIVER;
		else
			port = ANTENA_TRANSMITTER;
		//send the port
		Device::getMessage(port);
	}

private:

};
