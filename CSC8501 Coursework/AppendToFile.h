#pragma once
#include "FileManager.h"

class AppendToFile : public FileManager
{
public:
	AppendToFile(const string file_name);
	~AppendToFile();

	void read_from_file();
	void add_to_file(const string value);
	void add_to_file(const string value1, const string value2);
	void store_users(BinarySearchTree* bst);
};
