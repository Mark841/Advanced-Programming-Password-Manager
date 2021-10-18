#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileManager.h"
#include "WriteToFile.h"
#include "AppendToFile.h"
#include "BinarySearchTreeUsers.h"
#include "RandomPasswordGenerator.h"
#include "PasswordDecrypter.h"
#include "PasswordEncrypter.h"

using namespace std;

const string username_and_passwords_file = "password.txt";
const string passwords_file = "passwordtest.txt";
const string english_words = "ukenglishwords.txt";

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
bool binary_search_words(vector<string> dictionary_words, string word)
{
	int left = 0;
	int right = dictionary_words.size();

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (dictionary_words[mid] == word)
			return true;
		else if (word < dictionary_words[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return false;
}

void output_sentence(vector<vector<string>> words, int index, string sentence)
{
	if (index == words.size())
	{
		cout << sentence << endl;
	}
	else
	{
		for (int i = 0; i < words[index].size(); i++)
		{
			sentence += words[index][i] + " ";
			output_sentence(words, index+1, sentence);
			sentence = sentence.substr(0, (sentence.length() - (words[index][i].length() + 1)));
		}
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
	cout << "\t5. Decrypt sentence" << endl;
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
		BinarySearchTreeUsers* bst = new BinarySearchTreeUsers();
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

		cout << "69442315412328461112146111348510639151211334237202041103" << endl;
		PasswordDecrypter* decrypted = new PasswordDecrypter("69442315412328461112146111348510639151211334237202041103");
		decrypted->single_combination_decrypter();
		decrypted->output_possible_combinations();
		delete decrypted;

		PasswordDecrypter* decryption_attempt[20000];
		for (int i = 0; i < passwords.size()/2; i++)
		{
			cout << i << ",";
			decryption_attempt[i] = new PasswordDecrypter(passwords[i]);
			decryption_attempt[i]->single_combination_decrypter();
			decryption_attempt[i]->output_possible_combinations();
		}
		for (int i = passwords.size() / 2; i < passwords.size(); i++)
		{
			cout << i << ",";
			decryption_attempt[i] = new PasswordDecrypter(passwords[i]);
			decryption_attempt[i]->single_extended_combination_decrypter();
			decryption_attempt[i]->output_possible_combinations();
		}
		for (int i = 0; i < passwords.size(); i++)
		{
			delete decryption_attempt[i];
		}
		delete file;
		file = NULL;
	}
	catch (const invalid_argument& iae) {
		cout << "unable to read data: " << iae.what() << "\n";
		exit(1);
	}
}
void choice_5()
{
	try
	{
		AppendToFile* file = new AppendToFile(english_words);
		vector<string> dictionary_words = file->get_values();

		cout << "Decrypting: 27322810313331033910211452912207344136146925461033281533271031012815108114101" << endl;
		PasswordDecrypter* decrypted = new PasswordDecrypter("27322810313331033910211452912207344136146925461033281533271031012815108114101");
		decrypted->single_combination_decrypter();
		decrypted->fast_sentence_decrypter();

		cout << "Getting valid English words from decrypted words" << endl;
		vector<vector<int>> all_possible_words = decrypted->get_all_words();
		vector<string> valid_words;
		for (auto word : all_possible_words)
		{
			string valid_word = "";
			for (int i = 0; i < word.size(); i++)
			{
				valid_word += char(word[i]);
			}

			auto iterator = find(dictionary_words.begin(), dictionary_words.end(), valid_word);
			if (iterator != dictionary_words.end())
			{
				valid_words.push_back(valid_word);
			}
			valid_word = "";
		}

		cout << "Getting all possible sentence variations" << endl;
		vector<string> sentence = decrypted->get_rough_sentence_words();
		vector<vector<string>> words_in_right_slots;
		for (auto word : sentence)
		{
			vector<string> word_slots;
			for (auto valid_word : valid_words)
			{
				if (valid_word.length() == word.length())
				{
					word_slots.push_back(valid_word);
				}
			}
			words_in_right_slots.push_back(word_slots);
			word_slots.clear();
		}

		output_sentence(words_in_right_slots, 0, "");

		delete decrypted;
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
		while (choice < 1 || choice > 5) {
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
		else if (choice == 5)
		{
			choice_5();
		}
		cout << "Would you like to choose a new option (y/n): ";
		cin >> restart;
		cout << endl;
		choice = 0;
	}

	return 0;
}