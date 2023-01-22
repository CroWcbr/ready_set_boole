#pragma once

#include <string>
#include <stack>
#include <iostream>
#include <map>
#include <vector>

#define Vec		std::vector
#define i32		int32_t

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
		std::string		_str_tree_cnf;

	private:
		void			make_tree(const std::string &str);
		void			clear_node(Node* node);
		void			clear_stack(std::stack<Node*> &_st_n);
		void			print_tree(Node* node) const;
		void			evol_negation_normal_form(Node* node);
		void			evol_conjunctive_normal_form(Node* node);
		void			evol_conjunction_at_the_end(Node* node);
		void			tree_to_string_update(Node* node, std::string &str);

		Node*			copy_node(Node* node);
		void			copy_all(Node* my_node, Node* other);

		bool			evol_key_map(Node* node, std::map<char, bool> &key_map);
		Vec<i32>		evol_key_map_sets(Node* node, std::map<char, Vec<i32>> &key_map);

	public:
		Tree() = delete;
		Tree(const Tree& src) = delete;
		Tree& operator=(const Tree& src) = delete;

		Tree(const std::string &str);
		~Tree();

		void			print() const;
		std::string		negation_normal_form();
		std::string		conjunctive_normal_form();
		bool			result_key_map(std::map<char, bool> &key_map);
		Vec<i32>		result_key_map_sets(std::map<char, Vec<i32>> &key_map);
};
