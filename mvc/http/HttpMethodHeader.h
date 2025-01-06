//
// Created by Tamuka Manjemu on 1/5/25.
//

#pragma once
#include <string>
#include <stdexcept>

namespace atlas {
namespace http {

enum class HttpMethod {
    GET,
    POST,
    PUT,
    DELETE,
    PATCH,
    HEAD,
    OPTIONS,
    TRACE,
    CONNECT
};

class HttpMethodUtil {
public:
    // Convert string to HttpMethod
    static HttpMethod fromString(const std::string& method) {
        if (method == "GET") return HttpMethod::GET;
        if (method == "POST") return HttpMethod::POST;
        if (method == "PUT") return HttpMethod::PUT;
        if (method == "DELETE") return HttpMethod::DELETE;
        if (method == "PATCH") return HttpMethod::PATCH;
        if (method == "HEAD") return HttpMethod::HEAD;
        if (method == "OPTIONS") return HttpMethod::OPTIONS;
        if (method == "TRACE") return HttpMethod::TRACE;
        if (method == "CONNECT") return HttpMethod::CONNECT;

        throw std::invalid_argument("Invalid HTTP method: " + method);
    }

    // Convert HttpMethod to string
    static std::string toString(HttpMethod method) {
        switch (method) {
            case HttpMethod::GET: return "GET";
            case HttpMethod::POST: return "POST";
            case HttpMethod::PUT: return "PUT";
            case HttpMethod::DELETE: return "DELETE";
            case HttpMethod::PATCH: return "PATCH";
            case HttpMethod::HEAD: return "HEAD";
            case HttpMethod::OPTIONS: return "OPTIONS";
            case HttpMethod::TRACE: return "TRACE";
            case HttpMethod::CONNECT: return "CONNECT";
            default: throw std::invalid_argument("Unknown HTTP method");
        }
    }

    // Check if method allows body
    static bool hasBody(HttpMethod method) {
        switch (method) {
            case HttpMethod::POST:
            case HttpMethod::PUT:
            case HttpMethod::PATCH:
                return true;
            default:
                return false;
        }
    }

    // Check if method is safe (doesn't modify resources)
    static bool isSafe(HttpMethod method) {
        switch (method) {
            case HttpMethod::GET:
            case HttpMethod::HEAD:
            case HttpMethod::OPTIONS:
            case HttpMethod::TRACE:
                return true;
            default:
                return false;
        }
    }

    // Check if method is idempotent
    static bool isIdempotent(HttpMethod method) {
        switch (method) {
            case HttpMethod::PUT:
            case HttpMethod::DELETE:
            case HttpMethod::GET:
            case HttpMethod::HEAD:
            case HttpMethod::OPTIONS:
            case HttpMethod::TRACE:
                return true;
            default:
                return false;
        }
    }
};

} // namespace http
} // namespace mvc