//
// Created by Tamuka Manjemu on 1/5/25.
//

// Response.hpp
#pragma once
#include "ContentTypeHeader.h"
#include "CookieHeader.h"
#include <string>
#include <map>
#include <vector>
#include <sstream>

namespace atlas {
namespace http {

class Response {
public:
    Response();

    // Status operations
    void setStatus(int code, const std::string& message = "");
    int getStatusCode() const;
    const std::string& getStatusMessage() const;

    // Header operations
    void setHeader(const std::string& key, const std::string& value);
    std::string getHeader(const std::string& key) const;

    // Cookie operations
    void setCookie(const CookieHeader& cookie);

    // Body operations
    void setBody(const std::string& content);
    const std::string& getBody() const;

    // Convenience methods
    void sendJson(const std::string& json);
    void sendText(const std::string& text);
    void sendHtml(const std::string& html);
    void redirect(const std::string& url);

    // Convert to string
    std::string toString() const;

    bool isSent() const;
    void markAsSent();

private:
    int statusCode;
    std::string statusMessage;
    std::map<std::string, std::string> headers;
    std::vector<CookieHeader> cookies;
    std::string body;
    bool sent;
};

}
}
