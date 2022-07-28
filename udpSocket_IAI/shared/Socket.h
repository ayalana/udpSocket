#include "iostream"
#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <system_error>
#include <string>
#include <iostream>
#include <winsock2.h>
#include "..\shared\Network.h"
#include "..\shared\IDD.h"
#include <stdio.h>
#include <vector>
#pragma once
#pragma comment (lib, "ws2_32")
using namespace std;
class Socket
{
public:
    Socket() {
        //this->IP= "10.100.102.4";
    }
    const string IP = "10.100.102.4";
    unsigned short PORT = 0;
    int BUFFLEN = sizeof(Controller);
    Message recvfrom(unsigned short port) {
         PORT = port;
        try
        {
            WSASession Session;
            UDPSocket udpSocket;
            char buffer[sizeof(Message)];
            udpSocket.Bind(port);
            while (1)
            {
               
                Message msg;
                sockaddr_in add = udpSocket.RecvFrom((char*)&msg, sizeof(buffer));
                //ControlMessage* controlMessage = new ControlMessage[BUFFLEN];
                //controlMessage = (ControlMessage*)buffer;
                return msg;
            }
        }
        catch (system_error& e)
        {
            cout << e.what();
        }
    }
    void sendto(unsigned short port,char* cm,string ip) {
        PORT = port;
        try
        {
            WSASession Session;
            UDPSocket Socket;
            char buffer[sizeof(ControlMessage)];
            Socket.SendTo(ip, port, cm, BUFFLEN);
            cout << "the data send..."<<endl;
        }
        catch (exception& ex)
        {
            cout << ex.what();
        }
    }
};
