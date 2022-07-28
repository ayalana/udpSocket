#pragma once
#ifndef idd5
#define idd5
#include "..\shared\IDD.h"
#endif 
#include "..\..\shared\Server_.h"
#include <thread>
#include "..\shared\Socket.h"
using namespace std;
class Device
{
/// <summary>
///A class that everyone realizes
/// ctor that received type program  and type of device
/// </summary>
public:
	Device(int device, int type) {
		this->Type = type;
		this->last = -1;
		this->device = device;

	}
	int device;
	int Type;
	Socket socket;
	unsigned int last = -1;
   //process that get messages and if need-return them.....
	 void getMessage(int port) {
		while (1) {
			Message message;
			message = socket.recvfrom(port);

			Header header = message.header;
			//check if it is message
			//and The message was sent for me by the opcod
			if (header.msgSync == (unsigned short)MSG_SYNC&& validOpCode(header.Opcode))
			//if (header.msgSync == (unsigned short)MSG_SYNC)
			{				
				//if it is control message
				if (header.Opcode != (unsigned short)(DATA_MSG_OPCODE))
				{
					ControlMessage cm = message.ctrlMsg;
						//if the message is not correct
						if (cm.header.msgCounter != (1 + this->last))
							cm.Ack = 0;
						else
							cm.Ack = 1;
					//change the opcode to the message
					cm.header.Opcode = retOpcode(cm.header.Opcode);
					this->last = cm.header.msgCounter;//update the count
					message.ctrlMsg = cm;
					//Checking where to move it
					if (Type == RECEIVER)
						socket.sendto(MANAGER_RECEIVER, (char*)&message, "10.100.102.4");
					else
						socket.sendto(MANAGER_TRANSMITTER, (char*)&message, "10.100.102.4");
				}
				//if it is data message
				else {
					//Checking where to move it
					if (Type == TRANSMITTER)
						socket.sendto(MODEM_RECEIVER, (char*)&message, "10.100.102.4");
					else
						socket.sendto(MANAGER_RECEIVER, (char*)&message, "10.100.102.4");
				}
			}
			//if it is not message
			else
				cout << "The message is invalid\n";
		}	
	}
	//Returns the inverted opcode
	unsigned short retOpcode(unsigned short OpCode) {
		if (OpCode == (unsigned short)MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE)
			return AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE;
		if (OpCode == (unsigned short)MANAGER_TO_MODEM_CONTROL_MSG_OPCODE)
			return MODEM_TO_MANAGER_CONTROL_MSG_OPCODE;
		if (OpCode == (unsigned short)MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE)
			return ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE;
	}
	//Checking if the message is intended for me according to the opcode
	bool validOpCode(unsigned short opCode) {

		return(device==	AMPLIFIER &&opCode == (unsigned short)MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE ||
			device==ANTENA&&opCode == (unsigned short)MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE ||
			device==MODEM&&opCode == (unsigned short)MANAGER_TO_MODEM_CONTROL_MSG_OPCODE);
	}
};


