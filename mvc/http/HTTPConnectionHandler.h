//
// Created by Tamuka Manjemu on 1/6/25.
//
#pragma once
#include "IConnectionHandler.h"
#include "RequestHeader.h"
#include "ResponseHeader.h"
#include <functional>
#include <memory>

namespace atlas {
    namespace server {

        using RequestHandler = std::function<http::Response(const http::Request&)>;

        class HTTPConnectionHandler : public IConnectionHandler {
        public:
            explicit HTTPConnectionHandler(RequestHandler handler)
                : requestHandler(handler) {}

            void handleConnection(int clientSocket) override {
                try {
                    auto request = parseRequest(clientSocket);
                    auto response = requestHandler(request);
                    sendResponse(clientSocket, response);
                } catch (const std::exception& e) {
                    http::Response errorResponse;
                    errorResponse.setStatus(500, "Internal Server Error");
                    errorResponse.setBody("Internal Server Error");
                    sendResponse(clientSocket, errorResponse);
                }
            }

        private:
            http::Request parseRequest(int clientSocket);
            void sendResponse(int clientSocket, const http::Response& response);
            std::string readLine(int clientSocket);

            RequestHandler requestHandler;
            static const size_t BUFFER_SIZE = 4096;
        };

        // Helper function to create a handler
        inline std::shared_ptr<IConnectionHandler> createHandler(RequestHandler handler) {
            return std::make_shared<HTTPConnectionHandler>(handler);
        }

    } // namespace server
} // namespace atlas