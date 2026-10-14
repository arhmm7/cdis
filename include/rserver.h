#ifndef RSERVER_H
#define RESERVER_H

/// @brief Initializes Server
/// @return  Server Listening Socket
SOCKET InitServer();

/// @brief Creates a new Thread for each request
/// @param param Pointer to Anything
/// @return 
DWORD WINAPI ClientThread(LPVOID param);


/// @brief Start the Server
/// @param ListenSocket Pointer to Server's Listening Socket
void RunServer(SOCKET *ListenSocket);

#endif