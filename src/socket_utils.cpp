#include "socket_utils.h"

SocketUtils *SocketUtils::instance = nullptr;
SocketUtils *SocketUtils::getInstance()
{
    std::lock_guard<std::mutex> lock(SocketUtils::mutex);
    if (instance == nullptr)
    {
        instance = new SocketUtils();
    }
    std::lock_guard<std::mutex> unlock(SocketUtils::mutex);
    return instance;
}

void SocketUtils::createSocket(int *socketFd)
{
    *socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (*socketFd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(*socketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &SocketUtils::opt, sizeof(SocketUtils::opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}

void SocketUtils::bindSocket(int *socketFd, char *ipAddress, int port)
{
    struct sockaddr_in address;
    address.sin_family = AF_INET;

    if (inet_pton(AF_INET, ipAddress, &address.sin_addr.s_addr) <= 0)
    {
        perror("Invalid ipAddress");
        exit(EXIT_FAILURE);
    }

    address.sin_port = htons(port);

    if (bind(*socketFd, (struct sockaddr *)&ipAddress, sizeof(ipAddress)) < 0)
    {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }
}

void SocketUtils::listenSocket(int *socketFd)
{
    if (listen(*socketFd, MAX_CONNECTIONS) < 0)
    {
        perror("Socket listening failed");
        exit(EXIT_FAILURE);
    }
}

void SocketUtils::acceptSocket(int *socketFd)
{
    int newSocket = accept(*socketFd, NULL, NULL);
    if (newSocket < 0)
    {
        perror("Socket accepting failed");
        exit(EXIT_FAILURE);
    }
}

void SocketUtils::closeSocket(int *socketFd)
{
    if (close(*socketFd) < 0)
    {
        perror("Socket closing failed");
        exit(EXIT_FAILURE);
    }
}
