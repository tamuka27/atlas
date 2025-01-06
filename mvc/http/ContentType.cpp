//
// Created by Tamuka Manjemu on 1/5/25.
//

#ifndef CONTENTTYPE2_H
#define CONTENTTYPE2_H

#include "ContentTypeHeader.h"

namespace atlas {
    namespace http {

        const std::string ContentTypeHeader::TEXT_PLAN = "text/plain";
        const std::string ContentTypeHeader::TEXT_HTML = "text/html";
        const std::string ContentTypeHeader::APPLICATION_JSON = "application/json";
        const std::string ContentTypeHeader::APPLICATION_XML = "application/xml";
        const std::string ContentTypeHeader::MULTIPART_FORM = "multipart/form-data";
        const std::string ContentTypeHeader::APPLICATION_FORM = "application/x-www-form-urlencoded";
    }
}



class ContentType {

};



#endif //CONTENTTYPE2_H
