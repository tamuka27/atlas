//
// Created by Tamuka Manjemu on 1/5/25.
//

#include "CookieHeader.h"
#include "RequestHeader.h"

namespace mvc {
    namespace http {

        Request::Request(HttpMethod method, const std::string& path)
            : method(method), path(path) {}

        HttpMethod Request::getMethod() const { return method; }
        const std::string& Request::getPath() const { return path; }
        const std::string& Request::getQueryString() const { return queryString; }
        const std::string& Request::getBody() const { return body; }
        const std::string& Request::getRemoteAddr() const { return remoteAddr; }

        void Request::setHeader(const std::string& key, const std::string& value) {
            headers[key] = value;
        }

        std::string Request::getHeader(const std::string& key) const {
            auto it = headers.find(key);
            return (it != headers.end()) ? it->second : "";
        }

        bool Request::hasHeader(const std::string& key) const {
            return headers.find(key) != headers.end();
        }

        void Request::setQueryParam(const std::string& key, const std::string& value) {
            queryParams[key] = value;
        }

        std::string Request::getQueryParam(const std::string& key) const {
            auto it = queryParams.find(key);
            return (it != queryParams.end()) ? it->second : "";
        }

        void Request::setPostParam(const std::string& key, const std::string& value) {
            postParams[key] = value;
        }

        std::string Request::getPostParam(const std::string& key) const {
            auto it = postParams.find(key);
            return (it != postParams.end()) ? it->second : "";
        }

        void Request::setCookie(const atlas::http::CookieHeader& cookie) {
            cookies[cookie.getName()] = cookie;
        }

        const atlas::http::CookieHeader* Request::getCookie(const std::string& name) const {
            auto it = cookies.find(name);
            return (it != cookies.end()) ? &it->second : nullptr;
        }

        void Request::setBody(const std::string& newBody) { body = newBody; }
        void Request::setRemoteAddr(const std::string& addr) { remoteAddr = addr; }
        void Request::setQueryString(const std::string& qs) { queryString = qs; }

    } // namespace http
} // namespace mvc