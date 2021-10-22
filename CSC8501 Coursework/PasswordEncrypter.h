#pragma once
#include <string>
#include <vector>

using namespace std;

class PasswordEncrypter
{
public:
	static int collatz_algorithm(int char_value);
	static string password_encrypter(const string password);
	static string password_encrypter(vector<int> password);
};