#pragma once
#include <iostream>

using namespace std;

struct word_node {
	string word;
	struct word_node* left;
	struct word_node* right;
};

class BinarySearchTreeWords
{
public:
	BinarySearchTreeWords();
	~BinarySearchTreeWords();
	void insert_word(const string word);
	void print_tree();
	void terminate_tree();
	bool search_for_word(const string word);

private:
	struct word_node* root;

	void insert_word_recursive(struct word_node** tree, const string word);
	void print_tree_recursive(struct word_node* tree);
	void terminate_tree_recursive(struct word_node* tree);
	bool search_for_word_recursive(struct word_node** tree, const string word);
};
