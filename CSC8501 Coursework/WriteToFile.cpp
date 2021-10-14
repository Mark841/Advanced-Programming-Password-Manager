#include "WriteToFile.h"

WriteToFile::WriteToFile(const string file_name) : FileManager(file_name, 2)
{
}

WriteToFile::~WriteToFile()
{
}

void WriteToFile::add_to_file(const string value)
{
	data_file.clear();
	data_file.seekg(0, ios::end);
	data_file << value << "\n";
}