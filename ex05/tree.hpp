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

		Node(char key, Node *left, Node *right):
			_key(key), _left(left), _right(right)
		{}

		Node(const Node& src) = delete;

		Node& operator=(const Node& src) = delete;

		~Node() {};
};

class Tree
{
	public:
		Node*			_root;
		std::string		_str_tree;
		std::string		_str_tree_nnf;

	private:
		void			make_tree(const std::string &str);
		void			clear_node(Node* node);
		void			clear_stack(std::stack<Node*> &_st_n);
		void			print_tree(Node* node) const;
		void			evol_negation_normal_form(Node* node);
		void			tree_to_string_update(Node* node, std::string &str);

		Node*			copy_node(Node* node);
		void			copy_all(Node* my_node, Node* other);

	public:
		Tree() = delete;
		Tree(const Tree& src) = delete;
		Tree& operator=(const Tree& src) = delete;

		Tree(const std::string &str);
		~Tree();

		void			print() const;
		std::string		negation_normal_form();
};
