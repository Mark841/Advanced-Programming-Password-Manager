#pragma once
#include "FileManager.h"

class WriteToFile : public FileManager
{
public: 
	WriteToFile(const string file_name);
	~WriteToFile();

	void add_to_file(const string value);
};

