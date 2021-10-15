#include "PasswordDecrypter.h"

PasswordDecrypter::PasswordDecrypter(string password) : encrypted_password(password)
{
	vector<int> pass;
	decrypter(0, 0, pass);
}

PasswordDecrypter::~PasswordDecrypter()
{
}

void PasswordDecrypter::decrypter(int end_of_prev_visited_character, int offset, vector<int> password)
{

	// for all ascii values, if that ascii collatz'd is the first, first two or first three characters of string then that letter is a valid one
	// then use that first, first two or first three characters as the offset for the next
	for (int i = 1; i <= 3; i++)
	{
		int end_of_next_char = end_of_prev_visited_character + i;
		int substring;

		// if the substring would be longer than the rest of the string (out of bounds)
		if (end_of_next_char > encrypted_password.length())
		{
			if (PasswordEncrypter::password_encrypter(password) == encrypted_password)
			{
				//output_vector(password);
				possible_combinations.push_back(password);
			}
			return;
		}
		else 
		{
			substring = stoi(encrypted_password.substr(end_of_prev_visited_character, i));
		}

		//cout << substring << endl;
		for (int j = 1; j < 256; j++)
		//for (int j = 65; j < 123; j++)
		{
			// if letter is found
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				// go to next letter
				//cout << substring << " , " << char(j) << endl;
				//cout << char(j);
				password.push_back(j);
				decrypter(end_of_next_char, substring, password);
				password.pop_back();
			}
		}
	}
}

void PasswordDecrypter::output_possible_combinations()
{
	for (int i = 0; i < possible_combinations.size(); i++)
	{
		for (int j = 0; j < possible_combinations[i].size(); j++)
		{
			cout << char(possible_combinations[i][j]);
		}
		cout << endl;
	}
}
void PasswordDecrypter::output_vector(vector<int> password)
{
	for (int i = 0; i < password.size(); i++)
	{
		cout << char(password[i]);
	}
	cout << endl;
}