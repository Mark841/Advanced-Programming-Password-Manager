#include "PasswordEncrypter.h"
#include <iostream>

int PasswordEncrypter::collatz_algorithm(int char_value)
{
	int steps_through = 0;
	while (char_value != 1)
	{
		(char_value % 2 == 0) ? (char_value = char_value / 2) : (char_value = ((3 * char_value) + 1));
		steps_through++;
	}
	return steps_through;
}

string PasswordEncrypter::password_encrypter(const string password)
{
	string encrypted_password = "";
	int offset = 0;

	for (char c : password)
	{
		int ascii_value = int(c);
		offset = PasswordEncrypter::collatz_algorithm(ascii_value + offset);
		encrypted_password += to_string(offset);
	}
	return encrypted_password;

}
string PasswordEncrypter::password_encrypter(vector<int> password)
{
	string encrypted_password = "";
	int offset = 0;

	for (auto ascii_value : password)
	{
		offset = PasswordEncrypter::collatz_algorithm(ascii_value + offset);
		encrypted_password += to_string(offset);
	}
	return encrypted_password;
}