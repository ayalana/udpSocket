// Receiver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../../shared/Device.h"
#include "../../shared/Idd.h"
#include "../../shared/PackegeAntena.h"
#include "../../shared/PackageManager.h"
#include "../../shared/PackageModem.h"

#include <iostream>
#include <vector>

int main()
{
    std::cout << "Receiver!\n";
    //A vector in which each object contains an opcode and a port
    std::vector<Controller> controllers = {
        {ANTENA_RECEIVER,MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE},
        {MODEM_RECEIVER,MANAGER_TO_MODEM_CONTROL_MSG_OPCODE}
    };

    Manager manager(controllers, RECEIVER);
    //Antena antena(ANTENA, RECEIVER);
    Modem modem(MODEM, RECEIVER);

    while (true)
    {
        this_thread::sleep_for(std::chrono::seconds(1));
    }


    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
