#include "tree.hpp"

Tree::Tree(const std::string &str)
{
	std::stack<Node*>	_st_n;

	for(size_t i = 0, len = str.size(); i < len; i++)
	{
		char c = str[i];

		if (c == '!')
		{
			i++;
			if (!(i < len && str[i] >= 'A' && str[i] <= 'Z'))
			{
				clear_stack(_st_n);
				if (i < len)
					throw std::runtime_error("Wrong bool in string after Negative: " + str.substr(0, i + 1));
				else
					throw std::runtime_error("No bool in string after Negative: " + str.substr(0, i));
			}
			_st_n.push(new Node(str[i], 1, NULL, NULL));
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			_st_n.push(new Node(c, 0, NULL, NULL));
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
			Node *right = _st_n.top();
			_st_n.pop();
			Node *left = _st_n.top();
			_st_n.pop();
			_st_n.push(new Node(c, 0, left, right));
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
		clear_node(node->_left);
		clear_node(node->_right);
		delete node;
	}
}

void	Tree::print_tree(Node* node)
{
	if (node != NULL)
	{
		std::cout << node << "\t" << (node->_neg == 1 ? "!" : "") << node->_key << "\t";
		std::cout << node->_left << "\t" << node->_right << std::endl;
		print_tree(node->_left);
		print_tree(node->_right);
	}
}

void	Tree::print()
{
	std::cout << "TREE print" << std::endl;
	std::cout << "root = " << (_root->_neg == 1 ? "!" : "") << _root->_key << std::endl;
	print_tree(_root);
	std::cout << "END TREE print" << std::endl;
}

bool	Tree::evol(Node* node)
{
	if (node->_left)
	{
		if (node->_key == '|')
			return (evol(node->_left) | evol(node->_right));
		else if (node->_key == '&')
			return (evol(node->_left) & evol(node->_right));
		else if (node->_key == '^')
			return (evol(node->_left) ^ evol(node->_right));
		else if (node->_key == '>')
			return (!evol(node->_left) | evol(node->_right));
		else if (node->_key == '=')
			return (!evol(node->_left) ^ evol(node->_right));
		else
			throw std::runtime_error("Unreachable");
	}
	else
	{
		bool res = _key_map->find(node->_key)->second;
		return (node->_neg ? !res : res);
	}
}

bool	Tree::result(std::map<char, bool> &key_map)
{
	_key_map = &key_map;
	return evol(_root);
}
