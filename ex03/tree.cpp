#include "tree.hpp"
#include <iostream>

Tree::Tree(const std::string &str)
{
	std::stack<Node*>	_st_n;

	for(size_t i = 0, len = str.size(); i < len; i++)
	{
		char c = str[i];
		if (c == '0' || c == '1'|| c == '!')
		{
			if (c == '!')
			{
				if (i < len && (str[i + 1] == '0' || str[i + 1] == '1'))
				{
					i++;
					c = (str[i] == '0' ? '1' : '0');
				}
				else
				{
					clear_stack(_st_n);
					if (i < len)
						throw std::runtime_error("Wrong bool in string after Negative: " + str.substr(0, i + 2));
					else
						throw std::runtime_error("No bool in string after Negative: " + str.substr(0, i + 1));
				}
			}
			Node *tmp = new Node;
			tmp->key = c;
			tmp->left = NULL;
			tmp->right = NULL;
			_st_n.push(tmp);
		}
		else if (c == '&' || c == '|' || \
				c == '^' || c == '>' || \
				c == '=')
		{
			if (_st_n.size() < 2)
			{
				clear_stack(_st_n);
				throw std::runtime_error("Wrong operator in string (no bool for last operator): " + str.substr(0, i + 1));
			}
			Node *tmp = new Node;
			tmp->key = c;
			tmp->right = _st_n.top();
			_st_n.pop();
			tmp->left = _st_n.top();
			_st_n.pop();
			_st_n.push(tmp);
		}
		else
		{	
			clear_stack(_st_n);
			throw std::runtime_error("Unknown symbol in string: " + str);
		}
	}

	if (_st_n.size() != 1)
	{	
		clear_stack(_st_n);
		throw std::runtime_error("Not enough operator: " + str);
	}
	_root = _st_n.top();
};

Tree::~Tree()
{
	clear_node(_root);
}

void	Tree::clear_stack(std::stack<Node*> &_st_n)
{
	while(!_st_n.empty())
	{
		clear_node(_st_n.top());
		_st_n.pop();
	}
}

void	Tree::clear_node(Node* node)
{
	if (node != NULL)
	{
		clear_node(node->left);
		clear_node(node->right);
		delete node;
	}
}

void	Tree::print_tree(Node* node)
{
	if (node != NULL)
	{
		std::cout << node << "\t" << node->key << "\t" << node->left << "\t" << node->right << std::endl;
		print_tree(node->left);
		print_tree(node->right);
	}
}

void	Tree::print()
{
	std::cout << "TREE print" << std::endl;
	std::cout << "root = " << _root->key << std::endl;
	print_tree(_root);
	std::cout << "END TREE print" << std::endl;
}

bool	Tree::evol(Node* node)
{
	if (node->left)
	{
		if (node->key == '|')
			return (evol(node->left) | evol(node->right));
		else if (node->key == '&')
			return (evol(node->left) & evol(node->right));
		else if (node->key == '^')
			return (evol(node->left) ^ evol(node->right));
		else if (node->key == '>')
			return (!evol(node->left) | evol(node->right));
		else if (node->key == '=')
			return (!evol(node->left) ^ evol(node->right));
		else
			throw std::runtime_error("Unreachable");
	}
	else
		return (node->key == '1');
}

bool	Tree::result()
{
	return evol(_root);
}
