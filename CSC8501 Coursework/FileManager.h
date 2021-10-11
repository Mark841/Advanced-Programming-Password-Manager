#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileManager
{
public:
	FileManager(const string file_name);
	~FileManager();

	void read_from_file();
	void add_to_file(const string value);
	void add_to_file(const string value1, const string value2);

private:
	fstream data_file;
};