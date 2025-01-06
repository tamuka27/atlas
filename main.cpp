#include "mvc/http/ResponseHeader.h"
#include "mvc/http/ResponseHeader.h"
#include "mvc/server/HttpServer.hpp"
#include <iostream>

int main() {
    try {
        mvc::HTTPServer server(8080);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}