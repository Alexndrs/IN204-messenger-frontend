#include <iostream>
#include <Winsock2.h>

int main()
{

    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);

    WSACleanup();

    return 0;
}