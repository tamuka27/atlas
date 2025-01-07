cmake_minimum_required(VERSION 3.30)
project(atlas)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Define source files
set(SOURCE_FILES
        main.cpp
        mvc/http/ContentType.cpp
        mvc/http/Cookie.cpp
        mvc/http/Request.cpp
        mvc/http/Response.cpp
        mvc/server/Server.cpp
)

# Define header files
set(HEADER_FILES
        mvc/http/ContentTypeHeader.h
        mvc/http/CookieHeader.h
        mvc/http/ResponseHeader.h
        mvc/http/HttpMethodHeader.h
        mvc/server/Server.h
        mvc/http/IConnectionHandler.h
        mvc/http/HTTPConnectionHandler.h
)

# Add executable with all source and header files
add_executable(${PROJECT_NAME}
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

# Add threading support
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)