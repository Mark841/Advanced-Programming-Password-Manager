#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileManager.h"
#include "WriteToFile.h"
#include "AppendToFile.h"
#include "BinarySearchTree.h"
#include "RandomPasswordGenerator.h"
#include "PasswordDecrypter.h"
#include "PasswordEncrypter.h"

using namespace std;

const string username_and_passwords_file = "password.txt";
const string passwords_file = "passwordtest.txt";

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
		AppendToFile* file = new AppendToFile(username_and_passwords_file);
		string* username = new string();
		string* password = new string();
		*username = "";
		*password = "";

		validate_username_and_password(username, password);
		*password = PasswordEncrypter::password_encrypter(*password);
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
		AppendToFile* file = new AppendToFile(username_and_passwords_file);
		BinarySearchTree* bst = new BinarySearchTree();
		file->store_users_in_tree(bst);

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
				if (bst->get_user_password(username) == PasswordEncrypter::password_encrypter(password))
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
	try
	{
		WriteToFile* file = new WriteToFile(passwords_file);
		RandomPasswordGenerator* rpg = new RandomPasswordGenerator();

		string* restrictive_passwords = rpg->get_restrictive_passwords();
		vector<vector<int>> non_restrictive_passwords = rpg->get_non_restrictive_passwords();

		for (int i = 0; i < 10000; i++)
		{
			file->add_to_file(PasswordEncrypter::password_encrypter(restrictive_passwords[i]));
		}
		for (int i = 0; i < 10000; i++)
		{
			file->add_to_file(PasswordEncrypter::password_encrypter(non_restrictive_passwords[i]));
		}
		// TODO: 9999 not being saved to file but only on non restrictive passwords for some reason
		cout << PasswordEncrypter::password_encrypter(non_restrictive_passwords[9998]) << endl;
		cout << PasswordEncrypter::password_encrypter(non_restrictive_passwords[9999]) << endl;

		delete rpg;
		rpg = NULL;
	}
	catch (const invalid_argument& iae) {
		cout << "unable to read data: " << iae.what() << "\n";
		exit(1);
	}
}
void choice_4()
{
	try
	{
		AppendToFile* file = new AppendToFile(passwords_file);
		vector<string> passwords = file->get_values();

		cout << "20953985" << endl;
		PasswordDecrypter* decrypted = new PasswordDecrypter("20953985");
		decrypted->output_possible_combinations();
		delete decrypted;
		/*PasswordDecrypter* decryption_attempt[20000];
		for (int i = 0; i < passwords.size(); i++)
		{
			decryption_attempt[i] = new PasswordDecrypter(passwords[i]);
		}

		for (int i = 0; i < passwords.size(); i++)
		{
			delete decryption_attempt[i];
		}*/
		delete file;
		file = NULL;
	}
	catch (const invalid_argument& iae) {
		cout << "unable to read data: " << iae.what() << "\n";
		exit(1);
	}
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