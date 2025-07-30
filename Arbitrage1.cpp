#include "Arbitrage1.h"
#include "DBConnection.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    string user = "root";
    string database = "Arbitrage";
    string host = "localhost";
    string password = "Bhavsar%408780";
    unsigned int port = 33060;

    DBConnection db(host, user, password, database, port);

    try {
        if (db.connect()) {
            cout << "Connection Successfull";
        }
    }
    catch (const exception& e) {
        cerr << "[Main] Standard Exception: " << e.what() << endl;
    }

}
