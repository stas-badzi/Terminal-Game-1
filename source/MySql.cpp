#include "MySql.hpp"

#include <string>
#include <ctime>
#include <iostream>

using namespace std;

MySql::MySql(MySql::connection_details mysql_details) {
	con_details = mysql_details;
}


MySql::MySql(const char* server, const char* user, const char* password, const char* database, const unsigned int port) {
	con_details.server = server;
	con_details.user = user;
	con_details.password = password;
	con_details.database = database;
	con_details.port = port;

    while (!Retry_Connection()) {}

    string command = "INSERT INTO Users (Name)\nVALUES('player')";
    res = RunQuery(command.c_str());

    res = RunQuery("SELECT * FROM Users");
    while (row = mysql_fetch_row(res)) {
        player_id = atoi(row[0]);
    }
    #ifdef _WIN32
    //BOOL WINAPI* ConsoleHandlerB = new BOOL WINAPI;
    //ConsoleHandler;
    /*
        if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)(ConsoleHandler), true) == false) {
            exit(2);
        }
    */
    #endif

    

    return;
}

bool MySql::Retry_Connection(void) {
    con = mysql_init(NULL);

    if (!mysql_real_connect(con, con_details.server, con_details.user, con_details.password, con_details.database, con_details.port, NULL, 0)) {
        error = mysql_error(con);
        cout << error << '\n';
        return false;
    }
    return true;
}

MYSQL_RES* MySql::RunQuery(const char* sql_query) {
    if (mysql_query(con, sql_query)) {
        error = mysql_error(con);
        cout << error << '\n';
        return RunQuery(sql_query);
    }
    return mysql_use_result(con);
}

#ifdef _WIN32
    /*BOOL WINAPI MySql::ConsoleHandler(DWORD e) {
        if (e == CTRL_CLOSE_EVENT) {
            string command = "DELETE FROM Users\nWHERE ID = " + to_string(player_id);
            res = RunQuery(command.c_str());
            mysql_free_result(res);
            mysql_close(con);
        }

        return true;
    }*/


#endif