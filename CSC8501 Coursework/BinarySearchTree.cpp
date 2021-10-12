#include "BinarySearchTree.h"


BinarySearchTree::BinarySearchTree()
{
	root = NULL;
}
BinarySearchTree::~BinarySearchTree()
{
	terminate_tree();
	root = NULL;
}

void BinarySearchTree::insert_user(const string username, const string password)
{
	insert_user_recursive(&root, username, password);
}
void BinarySearchTree::print_tree()
{
	print_tree_recursive(root);
}
void BinarySearchTree::terminate_tree()
{
	terminate_tree_recursive(root);
}
bool BinarySearchTree::search_for_user(const string username)
{
	return search_for_user_recursive(&root, username);
}
string BinarySearchTree::get_user_password(const string username)
{
	return get_user_password_recursive(&root, username);
}


void BinarySearchTree::insert_user_recursive(struct node** tree, const string username, const string password)
{
	if (!tree) return;
	if (!(*tree))
	{
		*tree = new node;
		(*tree)->username = username;
		(*tree)->password = password;
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	if ((*tree)->username.compare(username) > 0)
	{
		insert_user_recursive(&(*tree)->left, username, password);
	}
	else if ((*tree)->username.compare(username) < 0)
	{
		insert_user_recursive(&(*tree)->right, username, password);
	}
}
void BinarySearchTree::print_tree_recursive(struct node* tree)
{
	if (tree)
	{
		print_tree_recursive(tree->left);
		cout << tree->username << endl;
		print_tree_recursive(tree->right);
	}
}
void BinarySearchTree::terminate_tree_recursive(struct node* tree)
{
	if (tree)
	{
		terminate_tree_recursive(tree->left);
		terminate_tree_recursive(tree->right);
		delete tree;
	}
}
bool BinarySearchTree::search_for_user_recursive(struct node** tree, const string username)
{
	if (*tree != NULL)
	{
		if ((*tree)->username == username)
		{
			return true;
		}
		else if ((*tree)->username > username)
		{
			return search_for_user_recursive(&(*tree)->left, username);
		}
		else if ((*tree)->username < username)
		{
			return search_for_user_recursive(&(*tree)->right, username);
		}
	}
	else
	{
		return false;
	}
}
string BinarySearchTree::get_user_password_recursive(node** tree, const string username)
{
	if (*tree != NULL)
	{
		if ((*tree)->username == username)
		{
			return (*tree)->password;
		}
		else if ((*tree)->username > username)
		{
			return get_user_password_recursive(&(*tree)->left, username);
		}
		else if ((*tree)->username < username)
		{
			return get_user_password_recursive(&(*tree)->right, username);
		}
	}
	else
	{
		return "";
	}
}
