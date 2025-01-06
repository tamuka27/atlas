//
// Created by Tamuka Manjemu on 1/5/25.
//

// Server.hpp
#pragma once
#include <string>
#include <functional>
#include <memory>
#include <thread>
#include <vector>
#include <atomic>
#include "mvc/http/RequestHandler.h"
#include "mvc/http/ResponseHandler.h"

namespace atlas {
namespace server {

class IConnectionHandler {
public:
    virtual ~IConnectionHandler() = default;
    virtual void handleConnection(int clientSocket) = 0;
};

class ServerConfig {
public:
    ServerConfig()
        : port(8080)
        , host("0.0.0.0")
        , maxConnections(100)
        , readTimeout(30)
        , writeTimeout(30) {}

    int port;
    std::string host;
    int maxConnections;
    int readTimeout;
    int writeTimeout;
};

class Server {
public:
    explicit Server(const ServerConfig& config = ServerConfig());
    virtual ~Server();

    // Server lifecycle
    virtual bool start();
    virtual void stop();
    bool isRunning() const { return running; }

    // Configuration
    void setConnectionHandler(std::shared_ptr<IConnectionHandler> handler) {
        connectionHandler = handler;
    }

    const ServerConfig& getConfig() const { return config; }

protected:
    virtual void acceptLoop();
    virtual void cleanupWorkers();

    ServerConfig config;
    std::atomic<bool> running;
    int serverSocket;
    std::vector<std::thread> workers;
    std::shared_ptr<IConnectionHandler> connectionHandler;
};

} // namespace server
} // namespace mvc

// Server.cpp
#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <algorithm>

namespace mvc {
namespace server {

Server::Server(const ServerConfig& config)
    : config(config)
    , running(false)
    , serverSocket(-1) {}

Server::~Server() {
    if (isRunning()) {
        stop();
    }
}

bool Server::start() {
    struct sockaddr_in address;

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        return false;
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Failed to set socket options: " << strerror(errno) << std::endl;
        close(serverSocket);
        return false;
    }

    // Set socket timeouts
    struct timeval timeout;
    timeout.tv_sec = config.readTimeout;
    timeout.tv_usec = 0;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        std::cerr << "Failed to set receive timeout: " << strerror(errno) << std::endl;
    }

    timeout.tv_sec = config.writeTimeout;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        std::cerr << "Failed to set send timeout: " << strerror(errno) << std::endl;
    }

    // Bind socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config.port);

    if (bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Failed to bind socket: " << strerror(errno) << std::endl;
        close(serverSocket);
        return false;
    }

    // Listen for connections
    if (listen(serverSocket, config.maxConnections) < 0) {
        std::cerr << "Failed to listen on socket: " << strerror(errno) << std::endl;
        close(serverSocket);
        return false;
    }

    running = true;
    std::cout << "Server started on port " << config.port << std::endl;

    // Start accept loop in a new thread
    workers.emplace_back(&Server::acceptLoop, this);

    return true;
}

void Server::stop() {
    running = false;

    if (serverSocket != -1) {
        close(serverSocket);
        serverSocket = -1;
    }

    cleanupWorkers();
}

void Server::acceptLoop() {
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    while (running) {
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                std::cerr << "Failed to accept connection: " << strerror(errno) << std::endl;
            }
            continue;
        }

        if (connectionHandler) {
            // Handle connection in a new thread
            workers.emplace_back([this, clientSocket]() {
                connectionHandler->handleConnection(clientSocket);
                close(clientSocket);
            });
        } else {
            close(clientSocket);
        }

        // Clean up completed worker threads
        cleanupWorkers();
    }
}

void Server::cleanupWorkers() {
    workers.erase(
        std::remove_if(
            workers.begin(),
            workers.end(),
            [](std::thread& t) {
                if (t.joinable()) {
                    t.join();
                    return true;
                }
                return false;
            }
        ),
        workers.end()
    );
}

} // namespace server
} // namespace mvc