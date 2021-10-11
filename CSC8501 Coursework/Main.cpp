#include <iostream>
#include <fstream>
#include <string>
#include "FileManager.h"

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

void create_username_and_password(string* username, string* password)
{
	while (*username == "" || username == nullptr)
	{
		cout << "Please enter a username: " << endl;
		cin >> *username;
	}
	while (*password == "" || password == nullptr)
	{
		cout << "Please enter a password: " << endl;
		cin >> *password;
	}
	*password = password_encrypter(*password);
}

int main()
{
	int choice = 0;
	while (choice < 1 || choice > 4) {
		choice = menu();
	}

	if (choice == 1)
	{
		try
		{
			FileManager* file = new FileManager(username_and_passwords_file);
			string* username = new string();
			string* password = new string();
			*username = "";
			*password = "";

			create_username_and_password(username, password);
			file->add_to_file(*username, *password);

			delete file;
			delete username, password;
			username, password = nullptr;
			file = NULL;
		}
		catch (const invalid_argument& iae) {
			cout << "unable to read data: " << iae.what() << "\n";
			exit(1);
		}
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