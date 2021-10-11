#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string username_and_passwords_file = "password.txt";
const string passwords_file = "passwordtest.txt";

int menu()
{
	int choice;
	cout << "Please enter an integer number which represents one of the choices below:" << endl;
	cout << "\t1. Create a username and password" << endl;
	cout << "\t2. Check username and password" << endl;
	cout << "\t3. Generate password strength analysis file" << endl;
	cout << "\t4. Analyse password strength analysis file" << endl;
	cin >> choice;
	return choice;
}

void file_retriever(const string file_name)
{
	ifstream data_file;
	data_file.open(file_name.c_str());

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	data_file.close();
}
void file_writer(const string username, const string password, const string file_name)
{
	ofstream data_file;
	data_file.open(file_name.c_str(), data_file.out | data_file.app);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	data_file << username << " " << password << "\n";

	data_file.close();
}

int collatz_algorithm(int char_value)
{
	int steps_through = 0;
	while (char_value != 1)
	{
		(char_value % 2 == 0) ? (char_value = char_value / 2) : (char_value = (3 * char_value + 1));
		steps_through++;
	}
	return steps_through;
}

string password_encrypter(const string password)
{
	string encrypted_password = "";
	int offset = 0;

	for (char c : password)
	{
		int ASCII_value = int(c);
		offset = collatz_algorithm(ASCII_value + offset);
		encrypted_password += to_string(offset);
	}
	return encrypted_password;
}

void create_username_and_password()
{
	try 
	{
		string username = "";
		string password = "";
		while (username == "")
		{
			cout << "Please enter a username: " << endl;
			cin >> username;
		}
		while (password == "")
		{
			cout << "Please enter a password: " << endl;
			cin >> password;
		}
		password = password_encrypter(password);
		cout << username << " " << password << endl;
		file_writer(username, password, username_and_passwords_file);
	}
	catch (const invalid_argument& iae) {
		cout << "unable to read data: " << iae.what() << "\n";
		exit(1);
	}
}

int main()
{
	int choice = 0;
	while (choice < 1 || choice > 4) {
		choice = menu();
	}

	if (choice == 1)
	{
		create_username_and_password();
	}
	else if (choice == 2)
	{
	}
	else if (choice == 3)
	{
	}
	else if (choice == 4)
	{
	}

	return 0;
}