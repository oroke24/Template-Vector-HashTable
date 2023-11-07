//By: Jamie O'Roke
//10/31/2023
//
#include<iostream>
#include<vector>
using namespace std;

//k means key, v means value
template<typename k, typename v>
struct Node{
	k key;
	v value;
	int index;

	Node * next;
	Node(k key, v value, int index): key(key), value(value), index(index){}
	void display_value(){cout << value;}
	int get_index(){return index;}
};

//class HashTable is implemented in the header file to avoid issues with locating
//template class methods during compile time
//The HashTable metods are as follows
//constructor Hashtable(size_t)
//destructor ~HashTable()
//size_t hash(string key)
//size_t hash(const int & key)
//void insert(const k& key, const v& value)
//void remove(const k& key, const v& value)
//v search(const k& key)
//----------------------------------------------------------------------------------------

template<class k, class v>
class HashTable{
	private:
	size_t table_size;
	std::vector<Node<k,v> *> buckets;

	public:
	//constructor and destructor
	HashTable(size_t size){
		table_size = size;
		buckets.reserve(table_size);
	}
	~HashTable(){
		for(typename vector<Node<k, v>*>::iterator it = buckets.begin(); it != buckets.end(); it++){
			Node<k, v> * current = *it;
			Node<k, v> * next = current->next;
		      	while(next){
				Node<k, v> * temp = next->next;
				delete next;
				next = nullptr;
				next = temp;
		        }	       
		}
		buckets.erase(buckets.begin(), buckets.end());
	}
//----------------------------------------------------------------------------------------
	//hash methods
	//
	size_t hash(string key){
		size_t sum = 0;
		for(char c : key){
			sum += c;
		}
		return sum % table_size;
	}
	size_t hash(const int& key){
		return key % table_size;
	}
//END HASH FUNCTIONS---------------------------------------------------------------------------------
	//Rest of the methods
	//
	void insert(const k& key, const v& value){
		size_t index = hash(key);
		if(buckets[index] != nullptr){
			Node<k, v> * prev = buckets[index]; 
			Node<k, v> * curr = buckets[index]->next; 
			while(curr){
				prev = curr;
				curr = curr->next;
			}
			curr = new Node(key, value, index);
			prev->next = curr;
		}
		else buckets.push_back(new Node(key, value, index));	
	}
//END INSERT----------------------------------------------------------------------------------------
	void remove(const k& key, const v& value){
		for(typename vector<Node<k, v>*>::iterator it = buckets.begin(); it != buckets.end(); it++){
			int index = hash(key);
			Node<k, v> * curr = *it;
			if(index == curr->index){ 
				if(!curr->next && curr->value == value) buckets.erase(it); 
				else if(curr->value == value){
					Node<k, v> * next = curr->next;
					curr->key = next->key;
					curr->value = next->value;
					curr->index = next->index;
					curr->next = next->next;
					delete next;
					next = nullptr;
				}
				
				else{
					Node<k, v> * prev = curr;
					while(curr && curr->value != value){
						prev = curr;
						curr = curr->next;
					}
					if(curr){
						prev->next = curr->next;
						delete curr;
						curr = nullptr;
					}
					else cout << value << " not found. . . " << endl;
				}

			}
		}
	}
//END REMOVE----------------------------------------------------------------------------------------

	v search(const k& key){
		int index = hash(key);
		for(typename vector<Node<k, v>*>::iterator it = buckets.begin(); it != buckets.end(); it++){
			Node<k, v> * curr = *it;	
			if(index = curr->get_index()) return curr->value;
		}
		return "NOT FOUND!";

	}
//END SEARCH----------------------------------------------------------------------------------------
	void display(){
		cout << "Testing iterator of vector of template nodes. . ." << endl;
		for(typename vector<Node<k, v>*>::iterator it = buckets.begin(); it != buckets.end(); it++){
			Node<k, v> * curr = *it; 
			cout << "index " << curr->get_index() << ": ";
			curr->display_value();
			cout << "->";
			while(curr->next){
				curr = curr->next;
				curr->display_value();
				cout << "->";
			}
			cout << endl;
//COMMENTED OUT PORTION FOR TESTING INDEXING INSTEAD OF VECTOR ITERATOR-----------------------------
		/*
		cout << "Testing indexing operator of template nodes (should be same as above). . ." << endl;
		for(size_t i = 0; i < buckets.size(); i++){
			Node<k, v> * curr = buckets[i]; 
			cout << "index: " << curr->get_index() << ": ";
			curr->display_value();
			cout << "->";
			while(curr->next){
				curr = curr->next;
				curr->display_value();
				cout << "->";
			}
			cout << endl;
		}
		cout << endl;
		*/
		}
	}
//END DISPLAY----------------------------------------------------------------------------------------
};
