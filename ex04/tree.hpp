#pragma once

#include <string>
#include <stack>
#include <iostream>
#include <map>

class Node {
	public:
		char	_key;
		Node	*_left;
		Node	*_right;

	public:
		Node() = delete;
		Node(const Node& src) = delete;
		Node& operator=(const Node& src) = delete;

		Node(char key, Node *left, Node *right):
			_key(key), _left(left), _right(right)
		{}
		~Node() {};
};

class Tree
{
	public:
		Node*					_root;
		std::map<char, bool>	*_key_map;

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
		bool	result(std::map<char, bool> &key_map);
};
