#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct HashNode {
	long key = -1;
	std::string value;
};

long capacity;
int size = 0;

struct HashNode** arr;
struct HashNode* dummy;


void insert(long key, std::string V)
{

	struct HashNode* temp
		= new HashNode;

	if (!temp)
	{
		return;
	}
	temp->key = key;
	temp->value = V;


	
	int hashIndex = key % capacity;

	
	while (arr[hashIndex] != NULL
		&& arr[hashIndex]->key != key
		&& arr[hashIndex]->key != -1) {
		hashIndex++;
		hashIndex %= capacity;
	}

	
	if (arr[hashIndex] == NULL
		|| arr[hashIndex]->key == -1)
		size++;

	arr[hashIndex] = temp;
}


int del(int key)
{
	
	int hashIndex = key % capacity;

	
	while (arr[hashIndex] != NULL) {
		
		if (arr[hashIndex]->key == key) {
			
			arr[hashIndex] = dummy;

			
			size--;

			
			return 1;
		}
		hashIndex++;
		hashIndex %= capacity;
	}

	
	return 0;
}


std::string find(int key)
{
	
	int hashIndex = (key % capacity);

	int counter = 0;

	
	while (arr[hashIndex] != NULL) {

		int counter = 0;
		
		if (counter++ > capacity)
			break;

		
		if (arr[hashIndex]->key == key)
			return arr[hashIndex]->value;

		hashIndex++;
		hashIndex %= capacity;
	}

	
	return "";
}


int main()
{

	int counter = 0;
	std::string tp;
	std::fstream newfile;
	newfile.open("tpoint.txt", std::ios::in); 
	if (newfile.is_open()) {   

		while (getline(newfile, tp)) { 

			if (counter == 0)
			{
				counter = std::stoi(tp);
				continue;
			}
			if (tp.find("size") != std::string::npos)
			{
				std::istringstream iss(tp);
				std::string s;
				std::getline(iss, s, ' ');
				std::getline(iss, s, ' ');
				capacity = std::stoi(s);
				arr = new HashNode * [std::stoi(s) + 1];
				for (int i = 0; i < std::stoi(s) + 1; i++)
					arr[i] = NULL;
				if (!arr) {
					return 1;
				}
			}
			if (tp.find("add") != std::string::npos)
			{

				std::istringstream iss(tp);
				std::string s;
				std::getline(iss, s, ' ');
				std::getline(iss, s, ' ');
				long id = std::stoi(s);
				std::getline(iss, s, ' ');
				std::string value = s;
				insert(id, value);
			}
			if (tp.find("print") != std::string::npos)
			{
				if (arr == NULL) {
					continue;
				}
				for (int i = 0; i < capacity; i++) {
					if (arr[i] != NULL) {
						std::cout << i << " " << arr[i]->key << " " << arr[i]->value << std::endl;
					}

				}
			}
			if (tp.find("delete") != std::string::npos)
			{
				std::istringstream iss(tp);
				std::string s;
				std::getline(iss, s, ' ');
				std::getline(iss, s, ' ');
				long id = std::stoi(s);
				del(id);
			}
			if (tp.find("stop") != std::string::npos)
			{
				if (arr == NULL) {
					continue;
				}
				delete* arr;
			}
		}
		newfile.close(); 

	}



	


	dummy
		= new HashNode;
	if (!dummy)
	{
		return 1;
	}
	dummy->key = -1;

	dummy->value = -1;

	return 0;


}
