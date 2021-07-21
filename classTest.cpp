#include <iostream>
#include <string>
#include <list>

using namespace std;

//polymorphic class
class HUMAN{
public:
	virtual ~HUMAN(){}

	int type = 0;
	string name;
};

//derived1
class WOYNERT: public HUMAN{
public:
	WOYNERT(){
		type = 1;
	}

	void print_msg(){
		cout << "Mi name is Woynert" << endl;
	}
};

//derived2
class REIDER: public HUMAN{
public:
	REIDER(){
		type = 2;
	}

	void print_info(){
		cout << "I like trains" << endl;
	}
};

int main(){

	cout << "Start" << endl;

	//create list
	list<HUMAN*> myList;
	myList.push_back(new HUMAN()  );
	myList.push_back(new WOYNERT());
	myList.push_back(new REIDER() );

	//iterate list
	list<HUMAN*>::iterator it;
	for (it = myList.begin(); it != myList.end(); it++){

		//if (dynamic_cast<WOYNERT*>(*it) != 0){
		cout << (*it)->type << endl;

		switch((*it)->type){

			//default human
			case 0:
				break;

			//woynert
			case 1:{
				WOYNERT* myW = dynamic_cast<WOYNERT*>(*it);
				myW->print_msg();
			}break;

			//reider
			case 2:{
				REIDER* myR = dynamic_cast<REIDER*>(*it);
				myR->print_info();
			}break;

			default:
				break;
		}

	}

	cout << "End" << endl;
	return 0;
}



/*
	A list containig these
	[INT ID, NODE* RAW_NODE]
	[INT ID, NODE* RAW_NODE]
	[INT ID, NODE* RAW_NODE]
	[INT ID, NODE* RAW_NODE]

	TODO
	Using an array of functions with containers as an argument (if needed)
*/

