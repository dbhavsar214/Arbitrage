#include "DBConnection.h"
#include <iostream>

DBConnection::DBConnection(const std::string& host,
    const std::string& user,
    const std::string& password,
    const std::string& database,
    unsigned int port)
    : host_(host), user_(user), password_(password), database_(database),
    port_(port), session_(nullptr), connected_(false) {
}

DBConnection::~DBConnection() {
    disconnect();
}

bool DBConnection::connect() {
    try {
        std::string connectionString = "mysqlx://" + user_ + ":" + password_ +
            "@" + host_ + ":" + std::to_string(port_);

        std::cout << "[DBConnection] Attempting to connect with connection string:\n  "
            << connectionString << std::endl;

        session_ = std::make_unique<mysqlx::Session>(connectionString);
        connected_ = true;

        std::cout << "[DBConnection] Connected successfully to " << host_
            << ":" << port_ << "/" << database_ << std::endl;
        return true;
    }
    catch (const mysqlx::Error& e) {
        std::cerr << "[DBConnection] Connection failed (MySQL error): " << e.what() << std::endl;
        session_.reset();
        connected_ = false;
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "[DBConnection] Connection failed (std error): " << e.what() << std::endl;
        session_.reset();
        connected_ = false;
        return false;
    }
    
}

void DBConnection::disconnect() {
    if (session_ && connected_) {
        try {
            session_->close();
            session_.reset();
            connected_ = false;
            std::cout << "[DBConnection] Connection closed.\n";
        }
        catch (const mysqlx::Error& e) {
            std::cerr << "[DBConnection] Error closing connection: " << e.what() << std::endl;
        }
    }
}




