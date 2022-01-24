#include <iostream>
#include <string>
#include "macros.h"
#include "lib/sqlite3.h"


//Macros
#define CALLBACK_GET_NODE_COUNT 0

using namespace std;

//classes
class SQL_TOOL;
class CALLBACK_PACK;

//allow to manage query callbacks
class CALLBACK_PACK{
public:
	SQL_TOOL* dbtool;
	int callback_case;
};

//way of accesing the db
class SQL_TOOL{
public:

	//properties
	sqlite3* DB;
	string url;

	int	node_count = 0;

	//open/create DB
	int open_database ()
	{
	    int exit = sqlite3_open(url.c_str(), &DB);

		//check error
	    if (exit) {
	        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	        return -1;
	    }
	    return 0;
	}

	//close
	void close_database ()
	{
	    sqlite3_close (DB);
	}

	//create Table
	int create_table (string query)
	{

	    char* msgError;
		int exit = 0;

		//execute query
	    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &msgError);

		//check query
	    if (exit != SQLITE_OK) {
	        cerr << "Error Create Table: " << msgError << endl;
	        sqlite3_free(msgError);
	    }
	    else cout << "Table created Successfully" << endl;

	    return (exit);
	}

	//callback
	static int callback (void* data, int argc, char** argv, char** azColName)
	{
		//convert void* to CALLBACK_PACK
		CALLBACK_PACK callback_pack = *((CALLBACK_PACK*) data);

		//get values
		SQL_TOOL* dbtool = callback_pack.dbtool;
		int option = callback_pack.callback_case;

		//case
		switch (option){
			case CALLBACK_GET_NODE_COUNT:
				cout << "Node amount: " << argv[0] << endl;
				(*dbtool).node_count = atoi(argv[0]);
				break;

			default:
				cout << "Warning. No callback case" << endl;
				return -1;
		}

		//print data
	    for (int i = 0; i < argc; i++) {
			cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	    }

	    return 0;
	}

	//select
	int select (sqlite3* DB, string query, int callback_case)
	{

		char* msgError;

		//callback pack for static function
		CALLBACK_PACK callback_pack;
		callback_pack.dbtool = this;
		callback_pack.callback_case = callback_case;

		//execute query
		int rc = sqlite3_exec(DB, query.c_str(), callback, (void*)&callback_pack, &msgError);

		//check
	    if (rc != SQLITE_OK){
	        cerr << "Error SELECT: " << msgError << endl;
			sqlite3_free(msgError);
		}
	    else cout << "Operation OK" << endl;

		return(rc);
	}

	//insert to table
	int insert (string query)
	{

		char* msgError;
		int exit = 0;

		//execute query
	    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &msgError);

		//check error
	    if (exit != SQLITE_OK) {
	        cerr << "Error: " << msgError << endl;
	        sqlite3_free(msgError);
	    }
	    //else std::cout << "Records created Successfully!" << std::endl;

		return (exit);
	}

};



//main
/*int main(int argc, char** argv)
{
    sqlite3* DB;
    int exit = 0;

    //open/create DB
    exit = sqlite3_open("databases/example.db", &DB);

	//check error
    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
        return (-1);
    }
    else
        cout << "Opened Database Successfully" << endl;

	//create table
	string query = "CREATE TABLE PERSON("
                   "ID INT PRIMARY KEY     NOT NULL, "
                   "NAME           TEXT    NOT NULL, "
                   "AGE            INT     NOT NULL);";

	create_table(DB, query);

	//insert info
	query = "INSERT INTO PERSON VALUES"
			"(1, 'STEVE', 10), (2, 'MARIO', 30);";
	insert(DB, query);

	//print table
	query = "SELECT * FROM PERSON";
	select(DB, query);

	//close
    sqlite3_close(DB);
    return (0);
} //*/
