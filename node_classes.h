#ifndef NODE_CLASSES
#define NODE_CLASSES

#include <iostream>
#include <string>
#include <list>
#include "macros.h"

using namespace std;

//title
class NODE{
public:

	int id;

	//properties
	int    node_type = NODE_TYPE_TITLE;
	string title     = "Untitled";

	NODE* node_parent = NULL;
	list<NODE*> children;

	//Polymorphic
	virtual ~NODE(){}

	//retitle node
	void set_title(string arg_title){
		this->title = arg_title;
	}
};

//text node
class NODE_TEXT: public NODE{
public:
	NODE_TEXT(){ node_type = NODE_TYPE_TEXT; }

	//properties
	string content = "";

	//setter
	void set_content (string arg_content){
		this->content = arg_content;
	}
};

//tarea node
class NODE_TAREA: public NODE_TEXT{
public:
	NODE_TAREA(){ node_type = NODE_TYPE_TAREA; }

	//properties
	bool   done = false;
	float  grade;
	string expiration_date;
};

#endif
