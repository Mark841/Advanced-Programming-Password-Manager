#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"

using namespace std;

class FileManager abstract
{
public:
	FileManager(const string file_name, int opening_mode);
	~FileManager();
	virtual void add_to_file(const string value) = 0;

protected:
	fstream data_file;
};