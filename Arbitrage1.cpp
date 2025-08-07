#include "Arbitrage1.h"
#include "DBConnection.h"
#include "WSConnection.h"
#include <string>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void connectToExchange(int port) {
    WSConnection ws;
    try {
        if (ws.setConnection(port)) {
            cout << "[INFO] WebSocket connected to port " << port << endl;
        }
    }
    catch (const exception& e) {
        cerr << "[ERROR] Exception on port " << port << ": " << e.what() << endl;
    }
}

int main() {
    string user = "root";
    string database = "Arbitrage";
    string host = "localhost";
    string password = "Bhavsar%408780";
    unsigned int port = 33060;
    DBConnection db(host, user, password, database, port);

    vector<int> ports = { 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009 };

    vector<thread> threads;
    for (int port : ports) {
        threads.emplace_back(thread(connectToExchange, port));
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();  // Optional: block forever since setConnection runs infinite loop
        }
    }

    return 0;
}
