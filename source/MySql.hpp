#pragma once
#include <mysql/mysql.h>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif


class MySql {
public:
	static struct connection_details {
		const char* server, * user, * password, * database;
		unsigned int port = 3005;
	};
	MySql(struct MySql::connection_details mysql_details);
	MySql(const char* server, const char* user, const char* password, const char* database, const unsigned int port);
	bool Retry_Connection(void);
	const char* error;
	MYSQL_RES* RunQuery(const char* sql_query);
	unsigned int player_id;
private:
	#ifdef _WIN32
		BOOL WINAPI ConsoleHandler(DWORD e);
	#else

	#endif
	MYSQL_RES* res;
	connection_details con_details;
	MYSQL* con;
	MYSQL_ROW row;
};

