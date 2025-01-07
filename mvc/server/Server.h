//
// Created by Tamuka Manjemu on 1/6/25.
//
#pragma once
#include <string>
#include <functional>
#include <memory>
#include <thread>
#include <vector>
#include <atomic>
#include "../http/RequestHeader.h"
#include "../http/ResponseHeader.h"
#include <netinet/in.h>

namespace atlas {
namespace server {

// Forward declarations
class IConnectionHandler;

class ServerConfig {
public:
    ServerConfig()
        : port(8080)
        , host("0.0.0.0")
        , maxConnections(100)
        , readTimeout(30)
        , writeTimeout(30)
        , backlogSize(10) {}

    int port;
    std::string host;
    int maxConnections;
    int readTimeout;
    int writeTimeout;
    int backlogSize;
};

using RequestHandler = std::function<http::Response(const http::Request&)>;

class Server {
public:
    explicit Server(const ServerConfig& config = ServerConfig());
    virtual ~Server();

    // Prevent copying
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    // Server lifecycle
    virtual bool start();
    virtual void stop();
    bool isRunning() const { return running; }

    // Connection handlers
    void setConnectionHandler(std::shared_ptr<IConnectionHandler> handler) {
        connectionHandler = handler;
    }

    void setRequestHandler(RequestHandler handler);

protected:
    virtual void acceptLoop();
    virtual void cleanupWorkers();
    bool setupSocket();
    void closeSocket();

    ServerConfig config;
    std::atomic<bool> running;
    int serverSocket;
    std::vector<std::thread> workers;
    std::shared_ptr<IConnectionHandler> connectionHandler;
    struct sockaddr_in serverAddr;
};

class IConnectionHandler {
public:
    virtual ~IConnectionHandler() = default;
    virtual void handleConnection(int clientSocket) = 0;
};

class HTTPConnectionHandler : public IConnectionHandler {
public:
    explicit HTTPConnectionHandler(RequestHandler handler)
        : requestHandler(handler) {}

    void handleConnection(int clientSocket) override;

private:
    http::Request parseRequest(int clientSocket);
    void sendResponse(int clientSocket, const http::Response& response);
    std::string readLine(int clientSocket);
    std::map<std::string, std::string> parseHeaders(int clientSocket);
    std::string readBody(int clientSocket, size_t contentLength);

    RequestHandler requestHandler;
    static const size_t BUFFER_SIZE = 4096;
};

} // namespace server
} // namespace atlas