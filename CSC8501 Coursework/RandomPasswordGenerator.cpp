#include "RandomPasswordGenerator.h"

RandomPasswordGenerator::RandomPasswordGenerator()
{
	restrictive_passwords = new string[10000];
	non_restrictive_passwords.resize(10000);
	repeated_characters_restricted();
	non_repeating_non_restrictive();
}
RandomPasswordGenerator::~RandomPasswordGenerator()
{
	delete [] restrictive_passwords;
}

void RandomPasswordGenerator::repeated_characters_restricted()
{
	int character_length = 0;
	string password;
	for (int i = 0; i < 10000; i++)
	{
		if (i % 100 == 0)
			character_length++;
		for (int j = 0; j < character_length; ++j)
		{
			password += char('a' + rand() % 26);
		}
		restrictive_passwords[i] = password;
		password = "";
	}
}
void RandomPasswordGenerator::non_repeating_non_restrictive()
{
	int character_length = 0;
	vector<int> password;
	int character;
	for (int i = 0; i < 10000; i++)
	{
		if (i % 100 == 0)
			character_length++;
		for (int j = 0; j < character_length; ++j)
		{
			character = rand() % 255 + 1;
			auto iterator = find(password.begin(), password.end(), character);
			while ((password.size() != 0) && (iterator != password.end()))
			{
				character = rand() % 255 + 1;
				iterator = find(password.begin(), password.end(), character);
			}
			password.push_back(character);
		}
		non_restrictive_passwords[i] = password;
		password.clear();
	}
}
