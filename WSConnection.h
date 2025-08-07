#ifndef WS_CONNECTION_H
#define WS_CONNECTION_H

#include <libwebsockets.h>
#include <string>

class WSConnection {
public:
    explicit WSConnection();
    bool setConnection(int port);

private:
    struct lws_context* context_;
    struct lws* wsi_;
};

#endif
