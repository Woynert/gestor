#include <iostream>
#include <string>
#include "lib/sqlite3.h"

//Macros
#define CALLBACK_GET_NODE_COUNT 0
#define NODE_TYPE_TITLE 0
#define NODE_TYPE_TEXT  1
#define NODE_TYPE_TAREA 2

using namespace std;

//classes
class DB_TOOL;
class CALLBACK_PACK;

//allow to manage query callbacks
class CALLBACK_PACK{
public:
	DB_TOOL* dbtool;
	int callback_case;
};

//way of accesing the db
class DB_TOOL{
public:

	//properties
	sqlite3* DB;
	string url;

	int	node_count = 0;

	//open/create DB
	int open_database(){
	    int exit = sqlite3_open(url.c_str(), &DB);

		//check error
	    if (exit) {
	        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	        return -1;
	    }
	    return 0;
	}

	//close
	void close_database(){
	    sqlite3_close(DB);
	}

	//create initial tables
	int start_tables(){
		string sql;
		sql = "CREATE TABLE NODES("
			"NODE_ID    INT PRIMARY KEY NOT NULL, "
			"NODE_TYPE  INT			    NOT NULL, "
			"NODE_TITLE TXT             NOT NULL, "
			"FATHER_ID  INT             NOT NULL);";

		sql += "CREATE TABLE TEXT_NODES("
			"NODE_ID INT PRIMARY KEY NOT NULL, "
			"CONTENT TXT             NOT NULL);";

		sql += "CREATE TABLE TAREA_NODES("
			"NODE_ID  INT PRIMARY KEY NOT NULL, "
			"DONE     BOOL            NOT NULL, "
			"GRADE    FLOAT           NOT NULL, "
			"EXPIRATION_DATE TXT              );";

		return createTable(DB, sql);
	}

	//create NEW NODE
	int create_node(int node_type, string title, int fatherId){

		int node_id = node_count+1;

		string sql = "INSERT INTO NODES VALUES("
		+ to_string(node_id)   + " , " //NODE_ID
		+ to_string(node_type) + " ,'" //NODE_TYPE
		+ title                + "','" //TITLE
		+ to_string(fatherId)  + "');";//FATHER_ID

		switch (node_type){
			case NODE_TYPE_TEXT:
				sql += "INSERT INTO TEXT_NODES VALUES("
				+ to_string(node_id) + " , " //NODE_ID
				+ "''"               + "); ";//CONTENT
				break;

			case NODE_TYPE_TAREA:
				sql += "INSERT INTO TAREA_NODES VALUES("
				+ to_string(node_id) + " , " //NODE_ID
				+ "FALSE"            + " , " //DONE
				+ "0.00"             + " , " //GRADE
				+ "NULL"             + "); ";//EXPIRATION_DATE
				break;
		}

		//insert
		int exit = insert(DB, sql);

		//check
		if (exit == SQLITE_OK){
			node_count++;
			printf("Finish insert %s node_count: %i exit: %i\n", title.c_str(), node_count, exit);
			return node_count;
		}
		else{
			printf("Finish insert %s node_count: %i exit: %i\n", title.c_str(), node_count, exit);
			return -1;
		}
	}

	void update_node_title(int node_id, int new_father_node_id ){
		/*
		if new_father is sibling of node:
		for child in node:
			child.father = node.father

		node.father = new_father


		*/

		string sql = "UPDATE NODES SET "
	}

	//Get variables to work with
	void update_info(){

		//node number
		string query = "SELECT COUNT(NODE_ID) FROM NODES;";
		select(DB, query, CALLBACK_GET_NODE_COUNT);

		cout << "Update_info. node_count: " << node_count << endl;
	}

private:

	//create Table
	int createTable(sqlite3* DB, string query){

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
	static int callback(void* data, int argc, char** argv, char** azColName)
	{
		//convert void* to CALLBACK_PACK
		CALLBACK_PACK callback_pack = *((CALLBACK_PACK*) data);

		//get values
		DB_TOOL* dbtool = callback_pack.dbtool;
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
	int select(sqlite3* DB, string query, int callback_case){

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
	int insert(sqlite3* DB, string query){

		char* msgError;
		int exit = 0;

		//execute query
	    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &msgError);

		//check error
	    if (exit != SQLITE_OK) {
	        cerr << "Error Insert: " << msgError << endl;
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

	createTable(DB, query);

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
