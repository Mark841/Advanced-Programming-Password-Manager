#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"

using namespace std;

class FileManager
{
public:
	FileManager(const string file_name);
	~FileManager();

	void read_from_file();
	void add_to_file(const string value);
	void add_to_file(const string value1, const string value2);
	void store_users(BinarySearchTree* bst);

private:
	fstream data_file;
};