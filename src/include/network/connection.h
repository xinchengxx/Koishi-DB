#ifndef KOISHIDB_SRC_INCLUDE_CONNECTION_H
#define KOISHIDB_SRC_INCLUDE_CONNECTION_H
#include <iostream>
#include <cstring>
#include <memory>

#include "network/request.h"
namespace koishidb {
    using std::string, std::unique_ptr;

    class connection {
    public:
        string read;
        string write;
        unique_ptr<request> req;

        connection() {
            req = nullptr;
        }
    };
};

#endif
