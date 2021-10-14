#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class RandomPasswordGenerator
{
public:
	RandomPasswordGenerator();
	~RandomPasswordGenerator();
	string* get_restrictive_passwords() { return restrictive_passwords; }
	vector<vector<int>> get_non_restrictive_passwords() { return non_restrictive_passwords; }

private:
	void repeated_characters_restricted();
	void non_repeating_non_restrictive();

	string* restrictive_passwords;
	vector<vector<int>> non_restrictive_passwords;

};