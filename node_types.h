#include <iostream>
#include <string>
#include <list>
using namespace std;

//title
class NODE{
	public:
		int node_type = 0;
		string title  = "Untitled";

		NODE*  node_parent     = NULL;
		list<NODE*> children;
		//int    children_amount = 0;
};

//text node
class TEXT_NODE: public NODE{
	public:
		string content;

		//setter
		void set_content (string arg_content){
			this->content = arg_content;
		}
};

//tarea node
class TAREA_NODE: public TEXT_NODE{
	public:
		bool   done;
		float  grade;
		string expiration_date;
};

//FUNCTIONS
//tree related
NODE* node_create         (int node_type, string title, NODE* node_parent);
void  node_delete		  (NODE* arg_node);
void  tree_delete         (NODE* arg_node);
void  node_update_parent  (NODE* argC       , NODE* argP);
bool  node_check_sibling  (NODE* node_parent, NODE* node_child);
void  print_tree_msg      (string msg, NODE* node       , int level);
void  print_tree_recursive(NODE* node       , int level);
void  tree_move			  (NODE* arg_node   , NODE* arg_parent);

//content related
void node_rename         (NODE* arg_node, string arg_title);

//create node
NODE* node_create(int node_type, string title, NODE* node_parent){

	//create
	NODE *new_node = new NODE;
	new_node->node_type   = node_type;
	new_node->title       = title;
	new_node->node_parent = node_parent;

	//set parent
	node_update_parent(new_node, node_parent);

	return new_node;
}

//delete node
void node_delete (NODE* arg_node){

	list<NODE*> children_rec;
	list<NODE*>::iterator it;

	//recopilate children
	for (it = arg_node->children.begin(); it != arg_node->children.end(); it++){
		children_rec.push_front(*it);
	}

	//reparent children
	for (it = children_rec.begin(); it != children_rec.end(); it++){
		cout << "Moving " << (*it)->title << endl;
		node_update_parent(*it, arg_node->node_parent);
	}

	//delete from parent
	arg_node->node_parent->children.remove(arg_node);

	//delete from memory
	delete(arg_node);
}

//delete entire node tree
void tree_delete(NODE* arg_node){

	list<NODE*> children_rec;
	list<NODE*>::iterator it;

	//recopilate children
	for (it = arg_node->children.begin(); it != arg_node->children.end(); it++){
		children_rec.push_front(*it);
	}

	//delete children from memory
	for (it = children_rec.begin(); it != children_rec.end(); it++){
		cout << "Deleting " << (*it)->title << endl;
		tree_delete(*it);
	}

	//delete from parent
	arg_node->node_parent->children.remove(arg_node);

	//delete from memory
	delete(arg_node);
}

//update parent
void node_update_parent(NODE* argC, NODE* argP){

	//avoid parent loop
	if (node_check_sibling(argC, argP)){
		cout << "True" <<  endl;

		bool child_has_parent = argC->node_parent != NULL;

		//iterate children
		list<NODE*>::iterator it;
		for (it = argC->children.begin(); it != argC->children.end(); it++)
		{
			//set new father
			(*it)->node_parent = argC->node_parent;

			//set new children
			if (child_has_parent)
				argC->node_parent->children.push_front( *it );
		}

		//clean children
		argC->children.clear();
	}

	//remove previous parenting
	if (argC->node_parent){
		argC->node_parent->children.remove( argC );
	}

	//set parent
	argP->children.push_front( argC );
	argC->node_parent = argP;
}

//move tree
void tree_move (NODE* arg_node, NODE* arg_parent){

	//avoid parent loop
	if (node_check_sibling(arg_node, arg_parent)){
		cout << "Error. Cant move tree to inside of itself" << endl;
		return;
	}
	else{
		//realocate parent
		node_update_parent(arg_node, arg_parent);
	}
	return;
}

//check its sibling
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

//retitle node
void node_rename(NODE* arg_node, string arg_title){
	arg_node->title = arg_title;
}

//print public
void print_tree_msg(string msg, NODE* node, int level){
	cout << "\n" << msg << endl;
	print_tree_recursive(node, level);
}

//print private
void print_tree_recursive(NODE* node, int level){

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
		print_tree_recursive(*it, level+1);
	}
}
