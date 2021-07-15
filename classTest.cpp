#include <iostream>
#include <string>
using namespace std;

class HUMAN{
	public:
		string name;
		int age;

		int printSecret(){
			cout << priv() << endl;
			return(1);
		}

	private:
		string priv(){
			return ("My secret");
		}
};

void printStringArray( string argv[] ){

	if (argv)
		for (int i = 0; i < 3; i++)
			cout << argv[i] << endl;
}

int main(){

	cout << "Start" << endl;
	//char** arr;
	//arr[0] = 's';

	//string arr[4] = {"Uno", "Dos", "Tres", "Cuatro"};
	//arr[5] = "Cinco";
	//arr[0] = "Hello";

	HUMAN woynert;


	char
	a = 'a',
	b = 'b';

	//char** arr = {};
	//cout << *arr << endl;

	char* ptr;
	ptr = new char('h');

	char** pptr;
	pptr = &ptr;

	*(pptr) = new char('b');
	*(pptr+1) = new char('c');

	cout << *(pptr) << endl;

	cout << "Hey" << endl;
	return 0;
}
