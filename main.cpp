//By: Jamie O'Roke
//10/31/2023
//
#include<iostream>
#include<fstream>
#include"hashtable.h"
using std::getline;
using std::string;
using std::cout;
using std::endl;

int main(){
	
	size_t size = 811;
	HashTable <int,string> intTable(size);
	HashTable <string,string> stringTable(size);

	cout << "hello world, lets make a hash table... " << endl;

	int keys[6] = {811, 0, 1623, 2435, 3247, 872};
	string values[6] = {"hello", "world", "how", "are", "you", "today?"};
	for(int i = 0; i < 6; i++){
		intTable.insert(keys[i], values[i]);
	}
	/*
	for(int i = 0; i < 6; i++){
		stringTable.insert(skeys[i], values[i]);
	}
	*/
	cout << "First example: HashTable<int, string> template" << endl;
	intTable.display();
	cout << "Removing key: 811, value \"hello\"" << endl;
	intTable.remove(811, "hello");
	cout << "New vector: " << endl;
	intTable.display();
	cout << "END FIRST EXAMPLE-------------------------------------------------------------\n"; 
	cout << "Second example: HashTable<string, string> template (loaded from local text file)" << endl;
	
	fstream myfile("hashtable_words.csv");
	string key, value;
	while(getline(myfile, key, ',') && myfile >> value){
		stringTable.insert(key, value);
	}
	stringTable.display();
	//intTable.search(keys[2]);
	return 0;
}

