//
// Created by Tamuka Manjemu on 1/6/25.
//

#pragma once

namespace atlas {
    namespace server {

        class IConnectionHandler {
        public:
            virtual ~IConnectionHandler() = default;
            virtual void handleConnection(int clientSocket) = 0;
        };

    } // namespace server
} // namespace atlas