//
// Created by Tamuka Manjemu on 1/6/25.
//
#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <algorithm>
#include <sstream>

namespace atlas {
namespace server {

Server::Server(const ServerConfig& config)
        : config(config)
        , running(false)
        , serverSocket(-1) {
}

Server::~Server() {
    if (isRunning()) {
        stop();
    }
}

bool Server::setupSocket() {
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        return false;
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Failed to set socket options: " << strerror(errno) << std::endl;
        closeSocket();
        return false;
    }

    // Set up server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(config.port);

    if (inet_pton(AF_INET, config.host.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address: " << strerror(errno) << std::endl;
        closeSocket();
        return false;
    }

    // Bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket: " << strerror(errno) << std::endl;
        closeSocket();
        return false;
    }

    // Listen for connections
    if (listen(serverSocket, config.maxConnections) < 0) {
        std::cerr << "Failed to listen on socket: " << strerror(errno) << std::endl;
        closeSocket();
        return false;
    }

    return true;
}

void Server::closeSocket() {
    if (serverSocket != -1) {
        close(serverSocket);
        serverSocket = -1;
    }
}

bool Server::start() {
    if (isRunning()) {
        std::cerr << "Server is already running" << std::endl;
        return false;
    }

    if (!setupSocket()) {
        return false;
    }

    running = true;
    workers.emplace_back(&Server::acceptLoop, this);
    std::cout << "Server started on " << config.host << ":" << config.port << std::endl;
    return true;
}

void Server::stop() {
    if (!isRunning()) {
        return;
    }

    running = false;
    closeSocket();
    cleanupWorkers();
    std::cout << "Server stopped" << std::endl;
}

void Server::acceptLoop() {
    while (running) {
        sockaddr_in clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            if (errno != EINTR && running) {
                std::cerr << "Failed to accept connection: " << strerror(errno) << std::endl;
            }
            continue;
        }

        if (connectionHandler) {
            workers.emplace_back([this, clientSocket]() {
                connectionHandler->handleConnection(clientSocket);
                close(clientSocket);
            });
        } else {
            close(clientSocket);
        }

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

void Server::setRequestHandler(RequestHandler handler) {
    auto httpHandler = std::make_shared<HTTPConnectionHandler>(handler);
    setConnectionHandler(httpHandler);
}

// HTTPConnectionHandler Implementation
void HTTPConnectionHandler::handleConnection(int clientSocket) {
    try {
        // For now, just send a basic response
        http::Response response;
        response.setStatus(200);
        response.setBody("<h1>Hello from Atlas Server!</h1>");
        sendResponse(clientSocket, response);
    } catch (const std::exception& e) {
        std::cerr << "Error handling connection: " << e.what() << std::endl;
        http::Response errorResponse;
        errorResponse.setStatus(500);
        errorResponse.setBody("Internal Server Error");
        sendResponse(clientSocket, errorResponse);
    }
}

void HTTPConnectionHandler::sendResponse(int clientSocket, const http::Response& response) {
    std::string responseStr = response.toString();
    send(clientSocket, responseStr.c_str(), responseStr.length(), 0);
}

// http::Request HTTPConnectionHandler::parseRequest(int clientSocket) {
//     std::string requestLine = readLine(clientSocket);
//     // Basic request parsing - will be enhanced later
//     return http::Request();
// }

std::string HTTPConnectionHandler::readLine(int clientSocket) {
    std::string line;
    char c;

    while (recv(clientSocket, &c, 1, 0) > 0) {
        line += c;
        if (c == '\n') break;
    }

    return line;
}

} // namespace server
} // namespace atlas