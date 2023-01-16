#pragma once

#include <string>
#include <stack>
#include <iostream>

typedef struct Tnode {
	char			key;
	struct Tnode	*left;
	struct Tnode	*right;
} Node;

class Tree
{
	public:
		Node*	_root;

	private:
		void	clear_node(Node* node);
		void	clear_stack(std::stack<Node*> &_st_n);
		void	print_tree(Node* node);
		bool	evol(Node* node);

	public:
		Tree() = delete;
		Tree(const Tree& src) = delete;
		Tree& operator=(const Tree& src) = delete;
		Tree(const std::string &str);
		~Tree();

		void	print();
		bool	result();
};
