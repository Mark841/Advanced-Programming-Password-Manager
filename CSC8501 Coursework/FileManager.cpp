#include "FileManager.h"

FileManager::FileManager(const string file_name, int opening_mode)
{
	if (opening_mode == 1)
	{
		data_file.open(file_name.c_str(), ios::out | ios::in | data_file.app);
	}
	else if (opening_mode == 2)
	{
		data_file.open(file_name.c_str(), ios::out | ios::trunc);
	}

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);
}
FileManager::~FileManager()
{
	data_file.close();
}