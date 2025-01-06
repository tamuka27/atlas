//
// Created by Tamuka Manjemu on 1/5/25.
//

#ifndef CONTENTTYPE_H
#define CONTENTTYPE_H

#endif //CONTENTTYPE_H

#pragma once
#include <string>

namespace atlas {
    namespace http {
        class ContentTypeHeader {
            public:
            static const std::string TEXT_PLAN;
            static const std::string TEXT_HTML;
            static const std::string APPLICATION_JSON;
            static const std::string APPLICATION_XML;
            static const std::string APPLICATION_FORM;
            static const std::string MULTIPART_FORM;
        };
    }
}
