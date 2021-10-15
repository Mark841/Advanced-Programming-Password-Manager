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

	void decrypter(int end_of_prev_visited_character, int offset, vector<int> password);
	void output_possible_combinations();
	void output_vector(vector<int> password);

private:
	string encrypted_password;
	vector<vector<int>> possible_combinations;
};

