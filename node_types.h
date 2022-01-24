#include <iostream>
#include <string>
#include <list>
#include "macros.h"
#include "node_classes.h"

using namespace std;



//FUNCTIONS
//tree related
NODE*      node_create          (int    node_type  , string title       , NODE* node_parent);
NODE_TEXT* node_text_create     (string title      , NODE*  node_parent );
void       node_delete		    (NODE*  arg_node   );
void       tree_delete          (NODE*  arg_node   );
void       node_update_parent   (NODE*  argC       , NODE*  argP        );
bool       node_check_sibling   (NODE*  node_parent, NODE*  node_child  );
void       print_tree_msg       (string msg        , NODE*  node        , int level);
void       print_tree_recursive (NODE*  node       , int    level       );
void       print_tree_info      (NODE*  node       , int    level       );
void       tree_move		    (NODE*  arg_node   , NODE*  arg_parent  );

//create node
NODE* node_create(int node_type, string title, NODE* node_parent){

	//create
	NODE* new_node;// = new NODE;

	switch(node_type){
		case NODE_TYPE_TITLE:
			new_node = new NODE();
			break;

		case NODE_TYPE_TEXT:
			new_node = new NODE_TEXT();
			break;

		case NODE_TYPE_TAREA:
			new_node = new NODE_TAREA();
			break;
	}

	//set
	//new_node->node_type   = node_type;
	new_node->title = title;

	// set id
	new_node->id = global.profile_seed + global.node_count;
	global.node_count += 1;

	// set parent
	if (node_parent)
	{
		new_node->node_parent = node_parent;

		node_update_parent(new_node, node_parent);
	}

	return new_node;
}


//
/*TEXT_NODE* node_text_create(string title, NODE* node_parent){

	//create base node
	NODE* base_node = node_create(title, node_parent);
	TEXT_NODE* text_node = dynamic_cast<TEXT_NODE*>( base_node );
	if (text_node == 0) cout << "Null pointer" << endl;

}*/

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

//print public
void print_tree_msg(string msg, NODE* node, int level, bool info){
	cout << "\n" << msg << endl;

	if (info)
		print_tree_info(node, level);
	else
		print_tree_recursive(node, level);
}

//print private
void print_tree_recursive(NODE* node, int level){

	// infinite loop
	if (level > 10){
		cout << "WARNING: Posible infinite loop\n";
	}

	//blank space
	string blank = " ";
	for (int i = 0; i < 2*level; i++)
		blank += " ";

	cout << node->id << blank << node->title << ":" << node->node_type << ":";

	//print parent
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

//print with extra info
void print_tree_info(NODE* node, int level){

	//avoid infinite loop
	if (level > 10) return;

	//blank space
	string blank;
	for (int i = 0; i < 2*level; i++)
		blank += " ";

	cout << blank << node->title;
	/*cout <<  ":" << node->node_type << ":";

	//print parent
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
	cout << endl;*/

	//print custom info
	//cout << blank;
	switch(node->node_type){
		case NODE_TYPE_TITLE:{
			cout << " TYPE TITLE" << endl;
		}break;

		case NODE_TYPE_TEXT:{
			NODE_TEXT* n_txt = dynamic_cast<NODE_TEXT*>(node);
			cout << " TYPE TEXT Content: " << n_txt->content << endl;
		}break;

		case NODE_TYPE_TAREA:{
			NODE_TAREA* n_tarea = dynamic_cast<NODE_TAREA*>(node);
			cout << " TYPE TAREA Done? " << n_tarea->done << endl;
		}break;
	}

	//recursion
	list<NODE*>::iterator it;
	for (it = node->children.begin(); it != node->children.end(); it++)
	{
		print_tree_info(*it, level+1);
	}
}
