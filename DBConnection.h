#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <string>
#include <memory>
#include <mysqlx/xdevapi.h>

class DBConnection {
public:
    DBConnection(const std::string& host,
        const std::string& user,
        const std::string& password,
        const std::string& database,
        unsigned int port = 33060);
    ~DBConnection();

    bool connect();
    void disconnect();
    mysqlx::Session* getSession();
    mysqlx::Schema getSchema();
    bool isConnected() const;

private:
    std::string host_;
    std::string user_;
    std::string password_;
    std::string database_;
    unsigned int port_;
    std::unique_ptr<mysqlx::Session> session_;
    bool connected_;
};

#endif // DB_CONNECTION_H