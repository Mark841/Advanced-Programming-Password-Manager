#include "AppendToFile.h"

AppendToFile::AppendToFile(const string file_name) : FileManager(file_name, 1)
{
}

AppendToFile::~AppendToFile()
{
}

void AppendToFile::read_from_file()
{
	string next_line;
	data_file.clear();
	data_file.seekg(0, ios::beg);

	while (getline(data_file, next_line))
	{
		cout << next_line << endl;
	}
}
vector<string> AppendToFile::get_values()
{
	vector<string> values;
	string next_line;

	data_file.clear();
	data_file.seekg(0, ios::beg);

	int count = 0;
	while (getline(data_file, next_line))
	{
		values.push_back(next_line);
	}
	return values;
}

void AppendToFile::add_to_file(const string value)
{
	data_file.clear();
	data_file.seekg(0, ios::end);
	data_file << value << "\n";
}
void AppendToFile::add_to_file(const string value1, const string value2)
{
	data_file.clear();
	data_file.seekg(0, ios::end);
	data_file << value1 << " " << value2 << "\n";
}

void AppendToFile::store_users_in_tree(BinarySearchTreeUsers* bst)
{
	string line;
	data_file.clear();
	data_file.seekg(0, ios::beg);

	while (getline(data_file, line))
	{
		bst->insert_user(line.substr(0, line.find(' ')), line.substr(line.find(' ') + 1));
	}
}

void AppendToFile::store_words_in_tree(BinarySearchTreeWords* bst)
{
	string line;
	data_file.clear();
	data_file.seekg(0, ios::beg);
	int count = 0;
	while (getline(data_file, line))
	{
		bst->insert_word(line);
		cout << count << endl;
		count++;
	}
}