#define DEFAULT_PORT "6379"

#if defined(_WIN32) || defined(_WIN64)

    #define WIN32_LEAN_AND_MEAN

    #include <windows.h>
    #include <winsock2.h>
    #include <WS2tcpip.h>
    #include <stdio.h> 
    #include <processthreadsapi.h>

    #pragma comment(lib, "Ws2_32.lib")

#endif

#include "rserver.h"

int main(int argc, char **argv) {

    SOCKET ListenSocket = InitServer();
    RunServer(&ListenSocket);
    return 0;

}