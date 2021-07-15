#include <iostream>
#include "sqlTool.h"

using namespace std;

int main(int argc, char** argv)
{
	DB_TOOL DB;
	DB.url = "databases/example.db";

	//setup
	DB.open_database();
	DB.start_tables();
	DB.update_info();

	//usage
	int node_quimica = DB.create_node(NODE_TYPE_TITLE ,"Calculo", -1);
	int node_derivadas = DB.create_node(NODE_TYPE_TEXT, "Derivadas", node_quimica);
	DB.create_node(NODE_TYPE_TEXT, "Integrales", node_quimica);

	DB.create_node(NODE_TYPE_TAREA, "Taller 1", node_quimica);
	DB.create_node(NODE_TYPE_TAREA, "Taller 2", node_quimica);

	//
	DB.update_node_title(node_quimica, node_derivadas);

	//close
	DB.close_database();

	cout << "Hello" << endl;

    return 0;
}

/*
	TIPOS DE NODOS
	0 TITULO (VACIO)
	1 TEXTO
	2 TAREAS
	3 CALIFICACIONES

	EJEMPLO
	- CALCULO
		+ TAREAS
		+ CALIFICACIONES
		- TEMAS
			+ DERIVADAS
			+ INTEGRALES

	TABLE NODES
	NODE_ID INT
	NODE_TYPE_ID INT
	NODE_TITLE TXT
	FATHER_ID INT

	TABLE TEXT_NODES
	NODE_ID INT
	CONTENT TXT

	TABLE TAREA_NODES
	NODE_ID INT
	CONTENT TXT
	DONE    BOOL
	GRADE   FLOAT
	EXPIRATION_DATE DATE (YYYY-MM-DD HH:MM:SS.SSS)

	PSEUDOCODE
	UPDATE PARENT (node, new_parent)
	if new_parent is sibling of node:
		for child in node:
			child.parent = node.parent

	node.parent = new_parent

	CHECK IS SIBLING (node, pos_parent)

	curr_parent = node.parent

	while(curr_parent != NULL):
		if curr_parent == pos_parent:
			return 1
		else:
			if curr_parent.parent != NULL:
				curr_parent = curr_parent.parent
			else break

	return 0


*/
