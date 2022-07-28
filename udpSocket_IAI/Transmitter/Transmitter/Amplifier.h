#include "..\..\shared\Device.h"
#pragma once
class Amplifier :Device
{
public:
	Amplifier(unsigned short port, unsigned short opcode, unsigned short returnOpCode, int type) :Device(port, opcode, returnOpCode, type) {
		this->returnOpCode = returnOpCode;
		std::thread t1(&Amplifier::getMessage, this);
		t1.detach();
	}
	Socket socket;
	unsigned short returnOpCode;
	void getMessage() {
		Device::getMessage(AMPLIFIER_TRANSMITTER);
	}
private:

};
