#include <iostream>
#include <iomanip>
#include "ArrayList.h"
#include "LinkedList.h"

using namespace std;


template <typename T>
void printList(List<T>& list)
{
	size_t i;
	for(i=0;i<list.size()-1;i++)
	{
		cout << list.at(i) << ",";
	}
	cout << list.at(i) << endl;
}


int main(int argc, char* argv[])
{

	cout << "Linked List tests:" << endl;

	LinkedList<int> list;
	
	cout << "List is size: " << list.size() << endl;
	cout << boolalpha << "List.empty() is " << list.empty() << endl;
	
 	list.append(1);
	list.append(2);
	list.append(3);
	list.append(4);
	list.append(5);
	
	printList<int>(list);
	
	cout << "List is size: " << list.size() << endl;
	cout << boolalpha << "List.empty() is " << list.empty() << endl;
	
	list.insert(0,99);
	
	printList<int>(list);
	
	list.remove(list.size()/2);
	
	printList<int>(list);

	cout << "Array-backed List tests:" << endl;

	ArrayList<int> list2;
	
	cout << "List is size: " << list2.size() << endl;
	cout << boolalpha << "List.empty() is " << list2.empty() << endl;
	
 	list2.append(1);
	list2.append(2);
	list2.append(3);
	list2.append(4);
	list2.append(5);
	
	printList<int>(list2);
	
	cout << "List is size: " << list2.size() << endl;
	cout << boolalpha << "List.empty() is " << list2.empty() << endl;
	
	list2.insert(0,99);
	
	printList<int>(list2);
	
	list2.remove(list2.size()/2);
	
	printList<int>(list2);
}
