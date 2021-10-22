#pragma once
#include <iostream>

using namespace std;

struct user_node {
	string username;
	string password;
	struct user_node* left;
	struct user_node* right;
};

class BinarySearchTreeUsers
{
public:
	BinarySearchTreeUsers();
	~BinarySearchTreeUsers();
	void insert_user(const string username, const string password);
	void print_tree();
	void terminate_tree();
	bool search_for_user(const string username);
	string get_user_password(const string username);
	
private:
	struct user_node* root;

	void insert_user_recursive(struct user_node** tree, const string username, const string password);
	void print_tree_recursive(struct user_node* tree);
	void terminate_tree_recursive(struct user_node* tree);
	bool search_for_user_recursive(struct user_node** tree, const string username);
	string get_user_password_recursive(struct user_node** tree, const string username);
};