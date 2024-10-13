#include <iostream>
#include <iomanip>
#include <vector>
#include "ArrayList.h"
#include "LinkedList.h"

using namespace std;

const std::string color_red = "\033[31m";
const std::string color_green = "\033[32m";
const std::string color_yellow = "\033[33m";
const std::string color_reset = "\033[0m";

template <typename T>
void printList(List<T>& list)
{
	for (size_t i = 0; i < list.size(); ++i)
	{
		cout << list.at(i) << (i < list.size() - 1 ? "," : "");
	}
	cout << endl;
}

template <typename T>
void validateList(List<T>& list, const T* expected, size_t expectedSize)
{
	bool isValid = true;

	if (list.size() != expectedSize)
	{
		isValid = false;
	}

	for (size_t i = 0; i < expectedSize; ++i)
	{
		if (list.at(i) != expected[i])
		{
			isValid = false;
			break;
		}
	}

	if (isValid)
	{
		cout << color_green << "Validation passed!" << color_reset << endl;
	}
	else
	{
		cout << color_red << "Validation failed!" << color_reset << endl;
		cout << "Expected: ";
		for (size_t i = 0; i < expectedSize; ++i)
		{
			cout << expected[i] << (i < expectedSize - 1 ? "," : "");
		}
		cout << endl;
		cout << "Got: ";
		printList(list);
	}
}

int main(int argc, char* argv[])
{
	cout << "Array List tests:" << endl;
	ArrayList<int> list;

	cout << color_yellow << "Initial state: " << color_reset << endl;
	cout << "List is size: " << list.size() << endl;
	cout << boolalpha << "List.empty() is " << list.empty() << endl;

	list.append(1);
	list.append(2);
	list.append(3);
	list.append(4);
	list.append(5);

	printList<int>(list);

	int expected1[5] = {1, 2, 3, 4, 5};
	validateList<int>(list, expected1, 5);
	
	cout << color_yellow << "\nAfter appending more values:" << color_reset << endl;
	cout << "List is size: " << list.size() << endl;
	cout << boolalpha << "List.empty() is " << list.empty() << endl;

	list.insert(0, 99);

	printList<int>(list);

	int expected2[6] = {99, 1, 2, 3, 4, 5};
	validateList<int>(list, expected2, 6);

	list.remove(list.size() / 2);

	printList<int>(list);

	int expected3[5] = {99, 1, 2, 4, 5};
	validateList<int>(list, expected3, 5);

	return 0;
}