#pragma once
#include <iostream>

using namespace std;

struct node {
	string username;
	string password;
	struct node* left;
	struct node* right;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
	void insert_user(const string username, const string password);
	void print_tree();
	void terminate_tree();
	bool search_for_user(const string username);
	string get_user_password(const string username);
	
private:
	struct node* root;

	void insert_user_recursive(struct node** tree, const string username2, const string password);
	void print_tree_recursive(struct node* tree);
	void terminate_tree_recursive(struct node* tree);
	bool search_for_user_recursive(struct node** tree, const string username);
	string get_user_password_recursive(struct node** tree, const string username);
};
