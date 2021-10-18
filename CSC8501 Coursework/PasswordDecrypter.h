#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "PasswordEncrypter.h"

using namespace std;

class PasswordDecrypter
{
public:
	PasswordDecrypter(string password);
	~PasswordDecrypter();

	void single_combination_decrypter();
	void single_combination_decrypter(int end_of_prev_visited_character, int offset, vector<int> password);
	void single_extended_combination_decrypter();
	void single_extended_combination_decrypter(int end_of_prev_visited_character, int offset, vector<int> password);
	
	void all_combinations_decrypter();
	void all_combinations_decrypter(int end_of_prev_visited_character, int offset, vector<int> password);
	
	void sentence_decrypter();
	void sentence_decrypter(int end_of_prev_visited_character, int offset, vector<int> password);
	
	void fast_sentence_decrypter();
	void fast_sentence_decrypter(int end_of_prev_visited_character, int offset, vector<int> password, vector<vector<int>>* words, vector<int> word);

	vector<vector<int>> get_all_words() { return *words; }
	vector<string> get_rough_sentence_words();
	void output_possible_combinations();
	void output_vector(vector<int> password);

private:
	string encrypted_password;
	vector<vector<int>> possible_combinations;
	vector<vector<int>>* words;
};

