#include <iostream>
#include <string>
#include "macros.h"
#include "sql_manager.h"
#include "node_classes.h"

// macros
using namespace std;

class DB_MANAGER{
public:

	//properties
	SQL_TOOL* DB = new SQL_TOOL();

	//open/create DB
	int start ()
	{
		DB->url = "./db/example.db";
		return DB->open_database ();
		return 0;
	}

	//close
	void close ()
	{
		return DB->close_database ();
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

		return DB->create_table(sql);
	}

	// add node
	int add_node(NODE* node){

		string sql = "INSERT INTO NODES VALUES("
		+ to_string(node->id)        + " , " //NODE_ID
		+ to_string(node->node_type) + " ,'" //NODE_TYPE
		+ node->title                + "','"; //TITLE

		if (node->node_parent){
			sql += to_string(node->node_parent->id); //FATHER_ID
		}
		else{
			sql += "-1";
		}

		sql += "');";

		/*switch (node_type){
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
		}*/

		//insert
		int exit = DB->insert(sql);

		printf("Finish insert %s node_count: %i exit: %i\n", node->title.c_str(), node->id, exit);

		if (exit == SQLITE_OK)
			return 0;
		return -1;
	}

	// delete node
	int delete_node(int node_id)
	{
		string sql = "DELETE FROM NODES WHERE NODE_ID = " + to_string(node_id) + ";";

		//insert
		int exit = DB->insert(sql);

		printf("Finish delete node id: %i exit: %i\n", node_id, exit);

		if (exit == SQLITE_OK)
			return 0;
		return -1;
	}

	// update node
	int update_node(NODE* node){

		string sql = "UPDATE NODES SET"
		"   NODE_TYPE  = "  + to_string(node->node_type)  +
		" , NODE_TITLE = '" + node->title +
		"', FATHER_ID  = ";

		if (node->node_parent){
			sql += to_string(node->node_parent->id); //FATHER_ID
		}
		else{
			sql += "-1";
		}

		sql += " WHERE NODE_ID = " + to_string(node->id) + ";";

		//insert
		int exit = DB->insert(sql);

		printf("Finish update node id: %i exit: %i\n", node->id, exit);

		if (exit == SQLITE_OK)
			return 0;
		return -1;
	}



	//create NEW NODE
	/*int create_node(int node_type, string title, int fatherId){

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
		int exit = BD.insert(sql);

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
	}*/


	/*/Get variables to work with
	void update_info(){

		//node number
		string query = "SELECT COUNT(NODE_ID) FROM NODES;";
		select(DB, query, CALLBACK_GET_NODE_COUNT);

		cout << "Update_info. node_count: " << node_count << endl;
	}*/

};
