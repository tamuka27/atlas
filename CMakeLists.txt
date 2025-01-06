cmake_minimum_required(VERSION 3.30)
project(atlas)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Add executable
add_executable(${PROJECT_NAME}
        src/main.cpp
        mvc/server/ServerHeader.h)

# Add threading support
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

add_executable(atlas main.cpp
        mvc/http/ContentTypeHeader.h
        mvc/http/ContentType.cpp
        mvc/http/CookieHeader.h
        mvc/http/Cookie.cpp
        mvc/http/Request.cpp
        mvc/http/ResponseHeader.h
        mvc/http/Response.cpp
        mvc/http/HttpMethodHeader.h
        mvc/server/HTTPServerHeader.h
        mvc/server/ServerHeader.h
)
