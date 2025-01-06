#pragma once
#include "HttpMethodHeader.h"
#include "CookieHeader.h"
#include <string>
#include <map>
#include <memory>

namespace atlas {
 namespace http {

  class Request {
  public:
   Request(HttpMethod method, const std::string& path);

   // Getters
   HttpMethod getMethod() const;
   const std::string& getPath() const;
   const std::string& getQueryString() const;
   const std::string& getBody() const;
   const std::string& getRemoteAddr() const;

   // Header operations
   void setHeader(const std::string& key, const std::string& value);
   std::string getHeader(const std::string& key) const;
   bool hasHeader(const std::string& key) const;

   // Parameter operations
   void setQueryParam(const std::string& key, const std::string& value);
   std::string getQueryParam(const std::string& key) const;
   void setPostParam(const std::string& key, const std::string& value);
   std::string getPostParam(const std::string& key) const;

   // Cookie operations
   void setCookie(const CookieHeader& cookie);
   const CookieHeader* getCookie(const std::string& name) const;

   // Setters for internal use
   void setBody(const std::string& body);
   void setRemoteAddr(const std::string& addr);
   void setQueryString(const std::string& qs);

  private:
   HttpMethod method;
   std::string path;
   std::string queryString;
   std::map<std::string, std::string> headers;
   std::map<std::string, std::string> queryParams;
   std::map<std::string, std::string> postParams;
   std::map<std::string, CookieHeader> cookies;
   std::string body;
   std::string remoteAddr;
  };

 } // namespace http
}
