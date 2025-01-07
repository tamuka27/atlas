//
// Created by Tamuka Manjemu on 1/5/25.
//

#ifndef COOKIE_H
#define COOKIE_H

#endif //COOKIE_H


#pragma once
#include <string>
#include <sstream>

namespace atlas {
    namespace http {

        class CookieHeader {
        public:
            CookieHeader() = default;
            CookieHeader(const std::string& name, const std::string& value);

            // Setters
            void setDomain(const std::string& domain);
            void setPath(const std::string& path);
            void setMaxAge(int maxAge);
            void setSecure(bool secure);
            void setHttpOnly(bool httpOnly);

            // Getters
            const std::string& getName() const;
            const std::string& getValue() const;
            const std::string& getDomain() const;
            const std::string& getPath() const;
            int getMaxAge() const;
            bool isSecure() const;
            bool isHttpOnly() const;

            // Convert to string for header
            std::string toString() const;

        private:
            std::string name;
            std::string value;
            std::string domain;
            std::string path;
            int maxAge{};
            bool secure{};
            bool httpOnly{};
        };
    }
}