#include "FileManager.h"

FileManager::FileManager(const string file_name)
{
	data_file.open(file_name.c_str(), ios::out | ios::in | data_file.app);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);
}

FileManager::~FileManager()
{
	data_file.close();
}

void FileManager::read_from_file()
{
	string next_line;
	data_file.clear();
	data_file.seekg(0, ios::beg);

	while (getline(data_file, next_line))
	{
		cout << next_line << endl;
	}
}

void FileManager::add_to_file(const string value)
{
	data_file.clear();
	data_file.seekg(0, ios::end);
	data_file << value << "\n";
}
void FileManager::add_to_file(const string value1, const string value2)
{
	data_file.clear();
	data_file.seekg(0, ios::end);
	data_file << value1 << " " << value2 << "\n";
}
