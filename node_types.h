#include <iostream>
#include <string>
#include <list>

//title
class NODE{
	public:
		int node_type = 0;
		string title  = "Untitled";

		//int parent_id;
		NODE*  node_parent     = NULL;
		//NODE** node_children   = NULL;
		list<NODE*> children;
		//int    children_amount = 0;
};

//text node
class TEXT_NODE: public NODE{
	public:
		string content;
};

//tarea node
class TAREA_NODE: public TEXT_NODE{
	public:
		bool   done;
		float  grade;
		string expiration_date;
};

//functions
void node_add_child(NODE* node, NODE* parent);
void node_add_child(NODE* parent, NODE* child);
bool node_check_sibling (NODE* node_parent, NODE* node_child);

NODE* node_create(int node_type, string title, NODE* node_parent){

	//create
	NODE *new_node = new NODE;
	new_node->node_type   = node_type;
	new_node->title       = title;
	new_node->node_parent = node_parent;

	//set parent
	node_add_child(node_parent, new_node);

	return new_node;
}

//ARREGLAR CONFUSION
void node_add_child(NODE* parent, NODE* child){

	//avoid parent loop
	if (node_check_sibling(child, parent)){
		cout << "True" <<  endl;

		bool child_has_parent = child->node_parent != NULL;

		//iterate children
		list<NODE*>::iterator it;
		for (it = child->children.begin(); it != child->children.end(); it++)
		{
			//set new father
			(*it)->node_parent = child->node_parent;

			//set new children
			if (child_has_parent)
				child->node_parent->children.push_front( *it );
		}
		child->children.clear();
	}

	//remove previous parenting
	if (child->node_parent){
		child->node_parent->children.remove( child );
	}

	//set parent
	parent->children.push_front(child);
	child->node_parent = parent;
}

bool node_check_sibling (NODE* node_parent, NODE* node_child){

	//parent interator
	NODE* curr_parent = node_child->node_parent;

	//loop
	while(curr_parent != NULL){

		//check its the same
		if (curr_parent == node_parent)
			return 1;
		else if (curr_parent->node_parent != NULL)
			curr_parent = curr_parent->node_parent;
		else
			break;
	}

	return 0;
}

//print
void print_tree(NODE* node, int level){

	//avoid infinite loop
	if (level > 10) return;

	for (int i = 0; i < 2*level; i++)
		cout << " ";

	cout << node->title << ":";

	if (node->node_parent)
		cout << node->node_parent->title;
	else
		cout << "NULL";
	cout << "/ ";

	//list children
	list<NODE*>::iterator it;
	for (it = node->children.begin(); it != node->children.end(); it++)
	{
		cout << (*it)->title << ", ";
	}
	cout << endl;

	//recursion
	for (it = node->children.begin(); it != node->children.end(); it++)
	{
		print_tree(*it, level+1);
	}
}
