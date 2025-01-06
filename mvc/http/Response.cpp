//
// Created by Tamuka Manjemu on 1/5/25.
//

#include "ResponseHeader.h"

namespace atlas {
namespace http {

Response::Response()
    : statusCode(200), statusMessage("OK"), sent(false) {
    setHeader("Content-Type", ContentTypeHeader::TEXT_HTML);
}

void Response::setStatus(int code, const std::string& message) {
    statusCode = code;
    statusMessage = message.empty() ? "OK" : message;
}

int Response::getStatusCode() const { return statusCode; }
const std::string& Response::getStatusMessage() const { return statusMessage; }

void Response::setHeader(const std::string& key, const std::string& value) {
    headers[key] = value;
}

std::string Response::getHeader(const std::string& key) const {
    auto it = headers.find(key);
    return (it != headers.end()) ? it->second : "";
}

void Response::setCookie(const CookieHeader& cookie) {
    cookies.push_back(cookie);
}

void Response::setBody(const std::string& content) {
    body = content;
    setHeader("Content-Length", std::to_string(content.length()));
}

const std::string& Response::getBody() const { return body; }

void Response::sendJson(const std::string& json) {
    setHeader("Content-Type", ContentTypeHeader::APPLICATION_JSON);
    setBody(json);
}

void Response::sendText(const std::string& text) {
    setHeader("Content-Type", ContentTypeHeader::TEXT_PLAN);
    setBody(text);
}

void Response::sendHtml(const std::string& html) {
    setHeader("Content-Type", ContentTypeHeader::TEXT_HTML);
    setBody(html);
}

void Response::redirect(const std::string& url) {
    setStatus(302);
    setHeader("Location", url);
}

std::string Response::toString() const {
    std::stringstream ss;

    // Status line
    ss << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n";

    // Headers
    for (const auto& header : headers) {
        ss << header.first << ": " << header.second << "\r\n";
    }

    // Cookies
    for (const auto& cookie : cookies) {
        ss << "Set-Cookie: " << cookie.toString() << "\r\n";
    }

    // Empty line separating headers from body
    ss << "\r\n";

    // Body
    ss << body;

    return ss.str();
}

bool Response::isSent() const { return sent; }
void Response::markAsSent() { sent = true; }

}
}
