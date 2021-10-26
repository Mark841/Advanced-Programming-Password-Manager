#include "BinarySearchTreeUsers.h"


BinarySearchTreeUsers::BinarySearchTreeUsers()
{
	root = NULL;
}
BinarySearchTreeUsers::~BinarySearchTreeUsers()
{
	terminate_tree();
	root = NULL;
}

void BinarySearchTreeUsers::insert_user(const string username, const string password)
{
	insert_user_recursive(&root, username, password);
}
void BinarySearchTreeUsers::print_tree()
{
	print_tree_recursive(root);
}
void BinarySearchTreeUsers::terminate_tree()
{
	terminate_tree_recursive(root);
}
bool BinarySearchTreeUsers::search_for_user(const string username)
{
	return search_for_user_recursive(&root, username);
}
string BinarySearchTreeUsers::get_user_password(const string username)
{
	return get_user_password_recursive(&root, username);
}

void BinarySearchTreeUsers::insert_user_recursive(struct user_node** tree, const string username, const string password)
{
	if (!tree) return;
	if (!(*tree))
	{
		*tree = new user_node;
		(*tree)->username = username;
		(*tree)->password = password;
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	if ((*tree)->username.compare(username) > 0)
		insert_user_recursive(&(*tree)->left, username, password);
	else if ((*tree)->username.compare(username) < 0)
		insert_user_recursive(&(*tree)->right, username, password);
}
void BinarySearchTreeUsers::print_tree_recursive(struct user_node* tree)
{
	if (tree)
	{
		print_tree_recursive(tree->left);
		cout << tree->username << endl;
		print_tree_recursive(tree->right);
	}
}
void BinarySearchTreeUsers::terminate_tree_recursive(struct user_node* tree)
{
	if (tree)
	{
		terminate_tree_recursive(tree->left);
		terminate_tree_recursive(tree->right);
		delete tree;
	}
}
bool BinarySearchTreeUsers::search_for_user_recursive(struct user_node** tree, const string username)
{
	if (*tree != NULL)
	{
		if ((*tree)->username == username)
			return true;
		else if ((*tree)->username > username)
			return search_for_user_recursive(&(*tree)->left, username);
		else if ((*tree)->username < username)
			return search_for_user_recursive(&(*tree)->right, username);
	}
	else
		return false;
}
string BinarySearchTreeUsers::get_user_password_recursive(user_node** tree, const string username)
{
	if (*tree != NULL)
	{
		if ((*tree)->username == username)
			return (*tree)->password;
		else if ((*tree)->username > username)
			return get_user_password_recursive(&(*tree)->left, username);
		else if ((*tree)->username < username)
			return get_user_password_recursive(&(*tree)->right, username);
	}
	else
		return "";
}
