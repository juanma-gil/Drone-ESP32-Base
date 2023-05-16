#pragma once

#include <mutex>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>

#define MAX_CONNECTIONS 1
#define BUFFER_SIZE 1024

class SocketUtils
{
    /*The constructor should always be private*/
protected:
    SocketUtils() {}
    static SocketUtils *instance;
    static std::mutex mutex;
    static int opt;

public:
    /*Should not be clonable*/
    SocketUtils(SocketUtils &other) = delete;
    /*Should not be assignale*/
    void operator=(const SocketUtils &) = delete;

    static SocketUtils *getInstance();
    static void createSocket(int *socketFd);
    static void bindSocket(int *socketFd, char *address, int port);
    static void listenSocket(int *socketFd);
    static void acceptSocket(int *socketFd);
    static void closeSocket(int *socketFd);
};