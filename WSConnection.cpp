#include "WSConnection.h"
#include <libwebsockets.h>
#include <iostream>
#include <cstring>
#include <csignal>

static volatile bool interrupted = false;

// Signal handler
static void signal_handler(int sig) {
    interrupted = true;
}

// Static callback function
static int callback_client(struct lws* wsi, enum lws_callback_reasons reason,
    void* user, void* in, size_t len) {
    switch (reason) {
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
        std::cout << "Client connected to server!" << std::endl;
        break;

    case LWS_CALLBACK_CLIENT_RECEIVE:
        std::cout << "Message from server: " << std::string((const char*)in, len) << std::endl;
        break;

    case LWS_CALLBACK_CLIENT_CLOSED:
        std::cout << "Connection closed by server." << std::endl;
        interrupted = true;
        break;

    default:
        break;
    }
    return 0;
}

// Define protocols
static struct lws_protocols protocols[] = {
    {
        "ws-client-protocol", callback_client, 0, 4096,
    },
    { nullptr, nullptr, 0, 0 }
};

WSConnection::WSConnection(const std::string& exAddress)
    : exAddress_(exAddress), context_(nullptr), wsi_(nullptr) {
}

bool WSConnection::setConnection() {
    signal(SIGINT, signal_handler); // Handle Ctrl+C

    lws_set_log_level(LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE, nullptr);

    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));

    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

    context_ = lws_create_context(&info);
    if (!context_) {
        std::cerr << "Failed to create WebSocket context\n";
        return false;
    }

    struct lws_client_connect_info ccinfo = {};
    ccinfo.context = context_;
    ccinfo.address = "localhost";             // Set your actual server address
    ccinfo.port = 1001;                       // Port number
    ccinfo.path = "/";
    ccinfo.host = lws_canonical_hostname(context_);
    ccinfo.origin = "origin";
    ccinfo.protocol = "ws-client-protocol";
    ccinfo.ssl_connection = 0;

    wsi_ = lws_client_connect_via_info(&ccinfo);
    if (!wsi_) {
        std::cerr << "Failed to connect to server\n";
        lws_context_destroy(context_);
        return false;
    }

    // Run the event loop
    while (!interrupted) {
        lws_service(context_, 100);
    }

    lws_context_destroy(context_);
    std::cout << "Exiting client cleanly.\n";
    return true;
}
