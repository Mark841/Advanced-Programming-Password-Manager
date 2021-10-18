#include "BinarySearchTreeWords.h"

BinarySearchTreeWords::BinarySearchTreeWords()
{
	root = NULL;
}
BinarySearchTreeWords::~BinarySearchTreeWords()
{
	terminate_tree();
	root = NULL;
}

void BinarySearchTreeWords::insert_word(const string word)
{
	insert_word_recursive(&root, word);
}
void BinarySearchTreeWords::print_tree()
{
	print_tree_recursive(root);
}
void BinarySearchTreeWords::terminate_tree()
{
	terminate_tree_recursive(root);
}
bool BinarySearchTreeWords::search_for_word(const string word)
{
	return search_for_word_recursive(&root, word);
}

void BinarySearchTreeWords::insert_word_recursive(struct word_node** tree, const string word)
{
	if (!tree) return;
	if (!(*tree))
	{
		*tree = new word_node;
		(*tree)->word = word;
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	if ((*tree)->word.compare(word) > 0)
	{
		insert_word_recursive(&(*tree)->left, word);
	}
	else if ((*tree)->word.compare(word) < 0)
	{
		insert_word_recursive(&(*tree)->right, word);
	}
}
void BinarySearchTreeWords::print_tree_recursive(struct word_node* tree)
{
	if (tree)
	{
		print_tree_recursive(tree->left);
		cout << tree->word << endl;
		print_tree_recursive(tree->right);
	}
}
void BinarySearchTreeWords::terminate_tree_recursive(struct word_node* tree)
{
	if (tree)
	{
		terminate_tree_recursive(tree->left);
		terminate_tree_recursive(tree->right);
		delete tree;
	}
}
bool BinarySearchTreeWords::search_for_word_recursive(struct word_node** tree, const string word)
{
	if (*tree != NULL)
	{
		if ((*tree)->word == word)
		{
			return true;
		}
		else if ((*tree)->word > word)
		{
			return search_for_word_recursive(&(*tree)->left, word);
		}
		else if ((*tree)->word < word)
		{
			return search_for_word_recursive(&(*tree)->right, word);
		}
	}
	else
	{
		return false;
	}
}
