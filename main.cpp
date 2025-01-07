#include "mvc/server/Server.h"
#include <iostream>

#include "mvc/http/RequestHeader.h"
#include "mvc/http/ResponseHeader.h"

#include "mvc/server/Server.h"
#include <iostream>

int main() {
    atlas::server::ServerConfig config;
    config.port = 8080;
    config.host = "0.0.0.0";

    atlas::server::Server server(config);

    server.setRequestHandler([](const atlas::http::Request& req) {
        atlas::http::Response resp;

        // Log incoming request

        // Basic routing
        if (req.getPath() == "/") {
            resp.setStatus(200);
            resp.setBody("<h1>Welcome to Atlas Server!</h1>"
                        "<p>Try these test routes:</p>"
                        "<ul>"
                        "<li><a href='/test'>Test Page</a></li>"
                        "<li><a href='/json'>JSON Response</a></li>"
                        "<li><a href='/headers'>Headers Info</a></li>"
                        "</ul>");
        }
        else if (req.getPath() == "/test") {
            resp.setStatus(200);
            resp.setBody("<h1>Test Page</h1><p>This is a test page</p>");
        }
        else if (req.getPath() == "/json") {
            resp.setStatus(200);
            resp.setHeader("Content-Type", "application/json");
            resp.setBody("{\"message\": \"Hello from JSON!\", \"status\": \"success\"}");
        }
        else if (req.getPath() == "/headers") {
            std::string headerInfo = "<h1>Request Headers</h1><pre>";
            // headerInfo += "Method: " + req.getMethod();
            headerInfo += "Path: " + req.getPath() + "\n";
            headerInfo += "User-Agent: " + req.getHeader("User-Agent") + "\n";
            headerInfo += "</pre>";

            resp.setStatus(200);
            resp.setBody(headerInfo);
        }
        else {
            resp.setStatus(404);
            resp.setBody("<h1>404 Not Found</h1><p>The requested page was not found.</p>");
        }

        return resp;
    });

    if (!server.start()) {
        std::cerr << "Failed to start server" << std::endl;
        return 1;
    }

    std::cout << "Server is running! You can test these URLs in your browser:" << std::endl;
    std::cout << "1. http://localhost:8080/ (Home page)" << std::endl;
    std::cout << "2. http://localhost:8080/test (Test page)" << std::endl;
    std::cout << "3. http://localhost:8080/json (JSON response)" << std::endl;
    std::cout << "4. http://localhost:8080/headers (Request headers info)" << std::endl;
    std::cout << "Press Enter to stop server..." << std::endl;

    std::cin.get();
    server.stop();
    return 0;
}