#include <iostream>
#include <fstream>
#include <string>
#include "FileManager.h"
#include "BinarySearchTree.h"

using namespace std;

const string username_and_passwords_file = "password.txt";
const string passwords_file = "passwordtest.txt";

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

void validate_username_and_password(string* username, string* password)
{
	// TODO: Check username against bst to see if already exists
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
}

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

void choice_1()
{
	try
	{
		FileManager* file = new FileManager(username_and_passwords_file);
		string* username = new string();
		string* password = new string();
		*username = "";
		*password = "";

		validate_username_and_password(username, password);
		*password = password_encrypter(*password);
		file->add_to_file(*username, *password);

		delete file, username, password;
		username, password = nullptr;
		file = NULL;
	}
	catch (const invalid_argument& iae) {
		cout << "unable to read data: " << iae.what() << "\n";
		exit(1);
	}
}
void choice_2()
{
	try
	{
		FileManager* file = new FileManager(username_and_passwords_file);
		BinarySearchTree* bst = new BinarySearchTree();
		file->store_users(bst);

		string username = "";
		cout << "Please enter a username: ";
		cin >> username;

		if (bst->search_for_user(username))
		{
			int password_attempts = 3;
			bool password_correct = false;
			string password = "";

			while (password_attempts > 0 && !password_correct)
			{
				cout << "Please enter your password (" << password_attempts << " guesses left): ";
				cin >> password;
				if (bst->get_user_password(username) == password_encrypter(password))
				{
					cout << "success!" << endl;
					password_correct = true;
				}
				password_attempts--;
			}
			if (password_attempts == 0 && !password_correct)
			{
				cout << "failure!" << endl;
			}
		}
		else
		{
			cout << "failure!" << endl;
		}

		delete file, bst;
		bst, file = NULL;
	}
	catch (const invalid_argument& iae) {
		cout << "unable to read data: " << iae.what() << "\n";
		exit(1);
	}
}
void choice_3()
{

}
void choice_4()
{

}

int main()
{
	int choice = 0;
	char restart = 'Y';
	while (toupper(restart) == 'Y')
	{
		while (choice < 1 || choice > 4) {
			choice = menu();
		}

		if (choice == 1)
		{
			choice_1();
		}
		else if (choice == 2)
		{
			choice_2();
		}
		else if (choice == 3)
		{
			choice_3();
		}
		else if (choice == 4)
		{
			choice_4();
		}
		cout << "Would you like to choose a new option (y/n): ";
		cin >> restart;
		cout << endl;
		choice = 0;
	}

	return 0;
}