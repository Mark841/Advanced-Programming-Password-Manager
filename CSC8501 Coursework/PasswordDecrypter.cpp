#include "PasswordDecrypter.h"
#include "AppendToFile.h"

PasswordDecrypter::PasswordDecrypter(string password) : encrypted_password(password)
{
	words = new vector<vector<int>>;
}
PasswordDecrypter::~PasswordDecrypter()
{
	delete words;
	words = NULL;
}

/* TODO:
I have this line in all my decrypt methods:

			if (substring == 0)
				return;

But the ASCII value 1 will give a value of 0 steps from the collatz algorithm so this is actually a vlaid character
*/

void PasswordDecrypter::single_combination_decrypter()
{
	vector<int> pass;
	single_combination_decrypter(0, 0, pass);
}
void PasswordDecrypter::single_combination_decrypter(int end_of_prev_visited_character, int offset, vector<int> password)
{
	for (int i = 1; i <= 3; i++)
	{
		int end_of_next_char = end_of_prev_visited_character + i;
		int substring;

		if (end_of_next_char > encrypted_password.length())
		{
			if (PasswordEncrypter::password_encrypter(password) == encrypted_password)
				possible_combinations.push_back(password);
			return;
		}
		else 
		{
			substring = stoi(encrypted_password.substr(end_of_prev_visited_character, i));
			if (substring == 0)
				return;
		}

		if (PasswordEncrypter::collatz_algorithm(32 + offset) == substring)
		{
			password.push_back(32);
			single_combination_decrypter(end_of_next_char, substring, password);
			password.pop_back();
		}
		for (int j = 65; j < 91; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				single_combination_decrypter(end_of_next_char, substring, password);
				password.pop_back();
			}
			if (possible_combinations.size() > 0)
				return;
		}
		for (int j = 97; j < 123; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				single_combination_decrypter(end_of_next_char, substring, password);
				password.pop_back();
			}
			if (possible_combinations.size() > 0)
				return;
		}
	}
}
void PasswordDecrypter::single_extended_combination_decrypter()
{
	vector<int> pass;
	single_extended_combination_decrypter(0, 0, pass);
}
void PasswordDecrypter::single_extended_combination_decrypter(int end_of_prev_visited_character, int offset, vector<int> password)
{
	for (int i = 1; i <= 3; i++)
	{
		int end_of_next_char = end_of_prev_visited_character + i;
		int substring;

		if (end_of_next_char > encrypted_password.length())
		{
			if (PasswordEncrypter::password_encrypter(password) == encrypted_password)
				possible_combinations.push_back(password);
			return;
		}
		else 
		{
			substring = stoi(encrypted_password.substr(end_of_prev_visited_character, i));
			if (substring == 0)
				return;
		}

		for (int j = 1; j < 256; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				single_extended_combination_decrypter(end_of_next_char, substring, password);
				password.pop_back();
			}
			if (possible_combinations.size() > 0)
				return;
		}
	}
}

void PasswordDecrypter::single_combination_decrypter(std::chrono::time_point<std::chrono::steady_clock> start_time, long float time_before_failure_in_seconds)
{
	vector<int> pass;
	single_combination_decrypter(start_time, time_before_failure_in_seconds, 0, 0, pass);
}
void PasswordDecrypter::single_combination_decrypter(std::chrono::time_point<std::chrono::steady_clock> start_time, long float time_before_failure_in_seconds, int end_of_prev_visited_character, int offset, vector<int> password)
{
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start_time).count();
	if (duration > time_before_failure_in_seconds)
		return;

	for (int i = 1; i <= 3; i++)
	{
		int end_of_next_char = end_of_prev_visited_character + i;
		int substring;

		if (end_of_next_char > encrypted_password.length())
		{
			if (PasswordEncrypter::password_encrypter(password) == encrypted_password)
				possible_combinations.push_back(password);
			return;
		}
		else 
		{
			substring = stoi(encrypted_password.substr(end_of_prev_visited_character, i));
			if (substring == 0)
				return;
		}

		if (PasswordEncrypter::collatz_algorithm(32 + offset) == substring)
		{
			password.push_back(32);
			single_combination_decrypter(start_time, time_before_failure_in_seconds, end_of_next_char, substring, password);
			password.pop_back();
		}
		for (int j = 65; j < 91; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				single_combination_decrypter(start_time, time_before_failure_in_seconds, end_of_next_char, substring, password);
				password.pop_back();
			}

			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start_time).count();
			if (duration > time_before_failure_in_seconds)
				return;

			if (possible_combinations.size() > 0)
				return;
		}
		for (int j = 97; j < 123; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				single_combination_decrypter(start_time, time_before_failure_in_seconds, end_of_next_char, substring, password);
				password.pop_back();
			}

			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start_time).count();
			if (duration > time_before_failure_in_seconds)
				return;

			if (possible_combinations.size() > 0)
				return;
		}
	}
}
void PasswordDecrypter::single_extended_combination_decrypter(std::chrono::time_point<std::chrono::steady_clock> start_time, long float time_before_failure_in_seconds)
{
	vector<int> pass;
	single_extended_combination_decrypter(start_time, time_before_failure_in_seconds, 0, 0, pass);
}
void PasswordDecrypter::single_extended_combination_decrypter(std::chrono::time_point<std::chrono::steady_clock> start_time, long float time_before_failure_in_seconds, int end_of_prev_visited_character, int offset, vector<int> password)
{
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start_time).count();
	if (duration > time_before_failure_in_seconds)
		return;

	for (int i = 1; i <= 3; i++)
	{
		int end_of_next_char = end_of_prev_visited_character + i;
		int substring;

		if (end_of_next_char > encrypted_password.length())
		{
			if (PasswordEncrypter::password_encrypter(password) == encrypted_password)
				possible_combinations.push_back(password);
			return;
		}
		else 
		{
			substring = stoi(encrypted_password.substr(end_of_prev_visited_character, i));
			if (substring == 0)
				return;
		}

		for (int j = 1; j < 256; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				single_extended_combination_decrypter(start_time, time_before_failure_in_seconds, end_of_next_char, substring, password);
				password.pop_back();
			}

			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start_time).count();
			if (duration > time_before_failure_in_seconds)
				return;

			if (possible_combinations.size() > 0)
				return;
		}
	}
}

void PasswordDecrypter::all_combinations_decrypter()
{
	vector<int> pass;
	all_combinations_decrypter(0, 0, pass);
}
void PasswordDecrypter::all_combinations_decrypter(int end_of_prev_visited_character, int offset, vector<int> password)
{
	for (int i = 1; i <= 3; i++)
	{
		int end_of_next_char = end_of_prev_visited_character + i;
		int substring;

		if (end_of_next_char > encrypted_password.length())
		{
			if (PasswordEncrypter::password_encrypter(password) == encrypted_password)
			{
				possible_combinations.push_back(password);
			}
			return;
		}
		else 
		{
			substring = stoi(encrypted_password.substr(end_of_prev_visited_character, i));
			if (substring == 0)
				return;
		}

		for (int j = 1; j < 256; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				all_combinations_decrypter(end_of_next_char, substring, password);
				password.pop_back();
			}
		}
	}
}

void PasswordDecrypter::sentence_decrypter()
{
	vector<int> pass;
	sentence_decrypter(0, 0, pass);
}
void PasswordDecrypter::sentence_decrypter(int end_of_prev_visited_character, int offset, vector<int> password)
{
	for (int i = 1; i <= 3; i++)
	{
		int end_of_next_char = end_of_prev_visited_character + i;
		int substring;

		if (end_of_next_char > encrypted_password.length())
		{
			if (PasswordEncrypter::password_encrypter(password) == encrypted_password)
			{
				output_vector(password);
			}
			return;
		}
		else 
		{
			substring = stoi(encrypted_password.substr(end_of_prev_visited_character, i));
			if (substring == 0)
				return;
		}
		if (PasswordEncrypter::collatz_algorithm(32 + offset) == substring)
		{
			password.push_back(32);
			sentence_decrypter(end_of_next_char, substring, password);
			password.pop_back();
		}
		for (int j = 65; j < 91; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				sentence_decrypter(end_of_next_char, substring, password);
				password.pop_back();
			}
		}
		for (int j = 97; j < 123; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				sentence_decrypter(end_of_next_char, substring, password);
				password.pop_back();
			}
		}
	}
}
void PasswordDecrypter::fast_sentence_decrypter()
{
	vector<int> pass, word;
	//cout << "Below are all unique words possible in the sentence, note some could be repeated more than once in the string" << endl;
	fast_sentence_decrypter(0, 0, pass, words, word);
	//cout << "Above are all unique words possible in the sentence, note some could be repeated more than once in the string" << endl;
}
void PasswordDecrypter::fast_sentence_decrypter(int end_of_prev_visited_character, int offset, vector<int> password, vector<vector<int>>* words, vector<int> word)
{
	if (words != NULL)
	{
		auto iterator = find(words->begin(), words->end(), word);
		if (iterator != words->end() && encrypted_password.length() < end_of_prev_visited_character + 1)
			return;
		else if (iterator != words->end() &&
			(PasswordEncrypter::collatz_algorithm(32 + offset) == stoi(encrypted_password.substr(end_of_prev_visited_character, 1)) ||
				PasswordEncrypter::collatz_algorithm(32 + offset) == stoi(encrypted_password.substr(end_of_prev_visited_character, 2)) ||
				PasswordEncrypter::collatz_algorithm(32 + offset) == stoi(encrypted_password.substr(end_of_prev_visited_character, 3))
				))
			return;
	}
	for (int i = 1; i <= 3; i++)
	{
		int end_of_next_char = end_of_prev_visited_character + i;
		int substring;

		if (end_of_next_char > encrypted_password.length())
		{
			if (PasswordEncrypter::password_encrypter(password) == encrypted_password)
			{
				words->push_back(word);
				word.clear();
				//output_vector(password);
			}
			return;
		}
		else
		{
			substring = stoi(encrypted_password.substr(end_of_prev_visited_character, i));
			if (substring == 0)
				return;
		}
		if (PasswordEncrypter::collatz_algorithm(32 + offset) == substring)
		{
			password.push_back(32);
			words->push_back(word);
			word.clear();
			fast_sentence_decrypter(end_of_next_char, substring, password, words, word);
			password.pop_back();
			//output_vector(password);
		}
		for (int j = 65; j < 91; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				word.push_back(j);
				fast_sentence_decrypter(end_of_next_char, substring, password, words, word);
				word.pop_back();
				password.pop_back();
			}
		}
		for (int j = 97; j < 123; j++)
		{
			if (PasswordEncrypter::collatz_algorithm(j + offset) == substring)
			{
				password.push_back(j);
				word.push_back(j);
				fast_sentence_decrypter(end_of_next_char, substring, password, words, word);
				word.pop_back();
				password.pop_back();
			}
		}
	}
}

vector<string> PasswordDecrypter::get_rough_sentence_words()
{
	vector<string> words;
	string word = "";
	for (int i = 0; i < possible_combinations[0].size(); i++)
	{
		if (possible_combinations[0][i] == 32)
		{
			words.push_back(word);
			word = "";
		}
		else
		{
			word += char(possible_combinations[0][i]);
		}
	}
	words.push_back(word);
	word = "";

	return words;
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