#define DEFAULT_PORT "6379"
#define BUFFER_SIZE 4096

#if defined(_WIN32) || defined(_WIN64)

    #define WIN32_LEAN_AND_MEAN

    #include <windows.h>
    #include <winsock2.h>
    #include <WS2tcpip.h>
    #include <stdio.h> 
    #include <processthreadsapi.h>

    #pragma comment(lib, "Ws2_32.lib")

#endif

DWORD WINAPI ClientThread(LPVOID param) {

        SOCKET ClientSocket = (SOCKET)(UINT_PTR)param;
        char request[BUFFER_SIZE];
        int received = recv(
            ClientSocket,
            request,
            sizeof(request) - 1,
            0
        );

        if (received > 0) {
            request[received] = '\0';

            printf("\nRequest Received ->\n%s\n", request);

        } else if (received == SOCKET_ERROR) {
            printf("recv failed: %d\n", WSAGetLastError());
        }

        shutdown(ClientSocket, SD_SEND);
        closesocket(ClientSocket);

}

SOCKET InitServer() {

    WSADATA wsaData;


    int iResult = 0;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0) {
        printf("Winsock Failed to Initialize! : %d\n",iResult);
        return 1;
    }

    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("Failed to Resolve Local Address and Port to be used by the server : %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET ListenSocket = INVALID_SOCKET;
    ListenSocket = socket(result->ai_family,result->ai_socktype,result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    if(listen(ListenSocket,SOMAXCONN) == SOCKET_ERROR) {
        printf( "Listen failed with error: %ld\n", WSAGetLastError() );
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    return ListenSocket;

}

void RunServer(SOCKET *ListenSocket) {

    for (;;) {

        SOCKET ClientSocket = accept(*ListenSocket, NULL, NULL); 

        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed: %d\n", WSAGetLastError());
            continue;
        }


        HANDLE threadHandle = CreateThread(
            NULL,
            0,
            ClientThread,
            (LPVOID)(UINT_PTR)ClientSocket,
            0,
            NULL
        );

       if (threadHandle == NULL) {
            printf("CreateThread failed: %lu\n", GetLastError());
            closesocket(ClientSocket);
            continue;
        }

        CloseHandle(threadHandle); 

    }
    closesocket(*ListenSocket);
    WSACleanup();

}