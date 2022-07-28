#include "..\..\shared\Device.h"
#pragma once
class Amplifier:Device
{
	/// <summary>
	/// ctor that received type program  and type of device
	/// and run process that get messages and if need-return them.....
	/// </summary>
	
	public:
	Amplifier(int device, int type) :Device(device, type) {
		std::thread t1(&Amplifier::getMessage, this);
		t1.detach();
	}
	//process that get messagesand if need - return them.....
	void getMessage() {
		Device::getMessage(AMPLIFIER_TRANSMITTER);
	}
private:

};
