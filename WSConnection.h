#ifndef WS_CONNECTION_H
#define WS_CONNECTION_H

#include <libwebsockets.h>
#include <string>

class WSConnection {
public:
    explicit WSConnection(const std::string& exAddress);
    bool setConnection();

private:
    std::string exAddress_;
    struct lws_context* context_;
    struct lws* wsi_;
};

#endif
