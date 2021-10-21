#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "FileManager.h"
#include "WriteToFile.h"
#include "AppendToFile.h"
#include "BinarySearchTreeUsers.h"
#include "RandomPasswordGenerator.h"
#include "PasswordDecrypter.h"
#include "PasswordEncrypter.h"

using namespace std;
using namespace std::chrono;

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

void output_sentence(vector<vector<string>> words, int index, string sentence, int* variations)
{
	if (index == words.size())
	{
		*variations = *variations + 1;
		cout << sentence << endl;
	}
	else
	{
		for (int i = 0; i < words[index].size(); i++)
		{
			sentence += words[index][i] + " ";
			output_sentence(words, index+1, sentence, variations);
			sentence = sentence.substr(0, (sentence.length() - (words[index][i].length() + 1)));
		}
	}
}

void analyse_character_set(vector<string> passwords, long float time_before_failure_in_seconds, int start, int end, void (PasswordDecrypter::* funcPtr)(std::chrono::time_point<std::chrono::steady_clock>, long float))
{
	PasswordDecrypter* cracking_attempt[10000];
	int count = 0;
	float entire_passwords_cracked = 0;
	float passwords_cracked = 0;
	unsigned long average = 0;
	int character_length = 1;

	cout << "Character length | Average successful cracking time (microseconds) | Success rate " << endl;
	for (int i = start; i < end; i++)
	{
		cracking_attempt[count] = new PasswordDecrypter(passwords[i]);
		auto start = high_resolution_clock::now();
		(cracking_attempt[count]->*funcPtr)(start, time_before_failure_in_seconds * 1000000);
		auto stop = high_resolution_clock::now();

		if (cracking_attempt[count]->get_all_combinations().size() != 0)
		{
			auto duration = duration_cast<microseconds>(stop - start).count();
			average += duration;
			entire_passwords_cracked++;
			passwords_cracked++;
		}

		if ((i + 1) % 100 == 0 && i != 0)
		{
			cout << "\t" << character_length << "\t |\t" << (average / 100) << " microseconds\t   |\t" << passwords_cracked << "%" << endl;
			average = 0;
			passwords_cracked = 0;
			character_length++;
		}
		count++;
	}
	cout << "Percentage success of passwords cracked: " << ((float)entire_passwords_cracked / ((float)passwords.size() - ((float)passwords.size() / 2))) * 100 << "% out of " << (passwords.size() / 2) << endl;
	for (int i = 0; i < 10000; i++)
	{
		delete cracking_attempt[i];
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
		long float time_before_failure_in_seconds = 0.25;
		void (PasswordDecrypter::*funcPtr)(std::chrono::time_point<std::chrono::steady_clock>, long float);

		cout << "\nCRACKING RESTRICTED ASCII CHARACTER SET\n\tNOTE: A password is given " << time_before_failure_in_seconds << "s to be cracked, if a solution isn't found it is counted as a failure\n" << endl;
		funcPtr = &PasswordDecrypter::single_restricted_combination_decrypter; 
		analyse_character_set(passwords, time_before_failure_in_seconds, 0, passwords.size() / 2, funcPtr);

		cout << "\nCRACKING NON RESTRICTED EXTENDED ASCII CHARACTER SET\n\tNOTE: A password is given " << time_before_failure_in_seconds << "s to be cracked, if a solution isn't found it is counted as a failure\n" << endl;
		funcPtr = &PasswordDecrypter::single_extended_combination_decrypter;
		analyse_character_set(passwords, time_before_failure_in_seconds, passwords.size() / 2, passwords.size(), funcPtr);
		
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
		decrypted->single_restricted_combination_decrypter();
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

		int possibilities = 0;
		int* variations = &possibilities;
		output_sentence(words_in_right_slots, 0, "", variations);
		cout << "\nThere were " << *variations << " possible different variations of sentences from fount valid English words" << endl;

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