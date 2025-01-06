//
// Created by Tamuka Manjemu on 1/5/25.
//

#include "CookieHeader.h"
namespace atlas {
    namespace http {


        CookieHeader::CookieHeader(const std::string& name, const std::string& value)
    : name(name), value(value), maxAge(-1), secure(false), httpOnly(false) {}

        void CookieHeader::setDomain(const std::string& domain) { this->domain = domain; }
        void CookieHeader::setPath(const std::string& path) { this->path = path; }
        void CookieHeader::setMaxAge(int maxAge) { this->maxAge = maxAge; }
        void CookieHeader::setSecure(bool secure) { this->secure = secure; }
        void CookieHeader::setHttpOnly(bool httpOnly) { this->httpOnly = httpOnly; }

        const std::string& CookieHeader::getName() const { return name; }
        const std::string& CookieHeader::getValue() const { return value; }
        const std::string& CookieHeader::getDomain() const { return domain; }
        const std::string& CookieHeader::getPath() const { return path; }
        int CookieHeader::getMaxAge() const { return maxAge; }
        bool CookieHeader::isSecure() const { return secure; }
        bool CookieHeader::isHttpOnly() const { return httpOnly; }

        std::string CookieHeader::toString() const {
            std::stringstream ss;
            ss << name << "=" << value;
            if (!domain.empty()) ss << "; Domain=" << domain;
            if (!path.empty()) ss << "; Path=" << path;
            if (maxAge >= 0) ss << "; Max-Age=" << maxAge;
            if (secure) ss << "; Secure";
            if (httpOnly) ss << "; HttpOnly";
            return ss.str();
        }


    }
}
