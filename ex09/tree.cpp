#include "tree.hpp"

Tree::Tree(const std::string &str)
{
	_str_tree = str;
	_root = NULL;
	make_tree(_str_tree);
};

Tree::~Tree()
{
	clear_node(_root);
}

void	Tree::make_tree(const std::string &str)
{
	std::stack<Node*>	_st_n;

	if (_root)
		clear_node(_root);
	for(size_t i = 0, len = str.size(); i < len; i++)
	{
		char c = str[i];

		if (c == '!')
		{
			if (_st_n.size() < 1)
			{
				clear_stack(_st_n);
				throw std::runtime_error("Wrong bool in string before Negative: " + str.substr(0, i + 1));
			}
			Node *left = _st_n.top();
			_st_n.pop();
			_st_n.push(new Node(str[i], left, NULL));
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			_st_n.push(new Node(c, NULL, NULL));
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
			_st_n.push(new Node(c, left, right));
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

void	Tree::print_tree(Node* node) const
{
	if (node != NULL)
	{
		std::cout << node << "\t" << node->_key << "\t";
		std::cout << node->_left << "\t" << node->_right << std::endl;
		print_tree(node->_left);
		print_tree(node->_right);
	}
}

void	Tree::print() const
{
	std::cout << "TREE print" << std::endl;
	std::cout << "root = " << _root->_key << std::endl;
	print_tree(_root);
	std::cout << "END TREE print" << std::endl;
}

void	Tree::evol_negation_normal_form(Node* node)
{
	if (node->_left)
	{
		if (node->_key == '!' && node->_left->_key == '!')
		{
			Node *tmp = node->_left;
			Node *tmp_left = tmp->_left;
			node->_key = tmp_left->_key;
			node->_left = tmp_left->_left;
			node->_right = tmp_left->_right;
			delete tmp_left;
			delete tmp;
			evol_negation_normal_form(_root);
		}
		else if (node->_key == '!' && node->_left->_key == '|')
		{
			Node *tmp = node->_left;
			node->_key = '&';
			node->_left = new Node('!', tmp->_left, NULL);
			node->_right = new Node('!', tmp->_right, NULL);
			delete tmp;
			evol_negation_normal_form(_root);
		}
		else if (node->_key == '!' && node->_left->_key == '&')
		{
			Node *tmp = node->_left;
			node->_key = '|';
			node->_left = new Node('!', tmp->_left, NULL);
			node->_right = new Node('!', tmp->_right, NULL);
			delete tmp;
			evol_negation_normal_form(_root);
		}
		else if (node->_key == '>')
		{
			node->_key = '|';
			node->_left = new Node('!', node->_left, NULL);
			evol_negation_normal_form(_root);
		}
		else if (node->_key == '=')
		{
			node->_key = '^';
			node->_left = new Node('!', node->_left, NULL);
			evol_negation_normal_form(_root);
		}
		else if (node->_key == '^')
		{
			node->_key = '|';
			Node *a = node->_left;
			Node *b = node->_right;
			node->_left = new Node('&', new Node('!', copy_node(a), NULL), copy_node(b));
			node->_right = new Node('&', a, new Node('!', b, NULL));
			evol_negation_normal_form(_root);
		}
		else
		{
			evol_negation_normal_form(node->_left);
			if (node->_right)
				evol_negation_normal_form(node->_right);
		}
	}
}

void	Tree::copy_all(Node* my_node, Node* other)
{
	Node	*l = other->_left;
	Node	*r = other->_right;
	if (other->_left == NULL)
		my_node->_left = NULL;
	else 
	{
		my_node->_left = new Node(l->_key, l->_left, l->_right);
		copy_all(my_node->_left, l);
	}
	if (other->_right == NULL)
		my_node->_right = NULL;
	else
	{
		my_node->_right = new Node(r->_key, r->_left, r->_right);
		copy_all(my_node->_right, r);
	}
}

Node*	Tree::copy_node(Node* node)
{
	Node	*tmp = new Node(node->_key, NULL, NULL);
	copy_all(tmp, node);
	return tmp;
}

void	Tree::tree_to_string_update(Node* node, std::string &str)
{
	if (node->_left)
	{
		if (node->_key == '!')
		{
			tree_to_string_update(node->_left, str);
			str += node->_key;
		}
		else
		{
			tree_to_string_update(node->_left, str);
			tree_to_string_update(node->_right, str);
			str += node->_key;
		}
	}
	else
		str += node->_key;
}

std::string	Tree::negation_normal_form()
{
	evol_negation_normal_form(_root);
	_str_tree_nnf.clear();
	tree_to_string_update(_root, _str_tree_nnf);
	return _str_tree_nnf;
}

void	Tree::evol_conjunctive_normal_form(Node* node)
{
	if (node->_key == '|' && \
		(node->_left->_key == '&' || node->_right->_key == '&'))
	{
		if (node->_left->_key == '&')
		{
			node->_key = '&';
			node->_left->_key = '|';
			Node *r = node->_right;
			node->_right = new Node('|', node->_left->_right, copy_node(r));
			node->_left->_right = r;
			evol_conjunctive_normal_form(_root);
		}
		else
		{
			node->_key = '&';
			node->_right->_key = '|';
			Node *l = node->_left;
			node->_left = new Node('|', copy_node(l), node->_right->_left);
			node->_right->_left = l;
			evol_conjunctive_normal_form(_root);
		}
	}
	else
	{
		if (node->_left)
			evol_conjunctive_normal_form(node->_left);
		if (node->_right)
			evol_conjunctive_normal_form(node->_right);
	}
}

void	Tree::evol_conjunction_at_the_end(Node* node)
{
	if ((node->_key == '|' && node->_left->_key == '|') ||
		(node->_key == '&' && node->_left->_key == '&'))
	{
		Node *node_left = node->_left;
		node->_left = node_left->_left;
		node_left->_left = node_left->_right;
		node_left->_right = node->_right;
		node->_right = node_left;
		evol_conjunction_at_the_end(node);
	}
	else
	{
		if (node->_left)
			evol_conjunction_at_the_end(node->_left);
		if (node->_right)
			evol_conjunction_at_the_end(node->_right);
	}
}

std::string	Tree::conjunctive_normal_form()
{
	evol_negation_normal_form(_root);
	evol_conjunctive_normal_form(_root);
	evol_conjunction_at_the_end(_root);
	_str_tree_cnf.clear();
	tree_to_string_update(_root, _str_tree_cnf);
	return _str_tree_cnf;
}

bool	Tree::evol_key_map(Node* node, std::map<char, bool> &key_map)
{
	if (node->_left)
	{
		if (node->_key == '!')
			return (!evol_key_map(node->_left, key_map));
		if (node->_key == '|')
			return (evol_key_map(node->_left, key_map) | evol_key_map(node->_right, key_map));
		else if (node->_key == '&')
			return (evol_key_map(node->_left, key_map) & evol_key_map(node->_right, key_map));
		else if (node->_key == '^')
			return (evol_key_map(node->_left, key_map) ^ evol_key_map(node->_right, key_map));
		else if (node->_key == '>')
			return (!evol_key_map(node->_left, key_map) | evol_key_map(node->_right, key_map));
		else if (node->_key == '=')
			return (!evol_key_map(node->_left, key_map) ^ evol_key_map(node->_right, key_map));
		else
			throw std::runtime_error("Unreachable");
	}
	else
		return (key_map.find(node->_key)->second);
}

bool	Tree::result_key_map(std::map<char, bool> &key_map)
{
	return evol_key_map(_root, key_map);
}

Vec<i32>	Tree::evol_key_map_sets(Node* node, std::map<char, Vec<i32>> &key_map)
{
	if (node->_key == '!')
		return {};
	else if (node->_left)
	{
		Vec<i32>	tmp;
		Vec<i32>	vector_left = evol_key_map_sets(node->_left, key_map);
		Vec<i32>	vector_right = evol_key_map_sets(node->_right, key_map);
		if (node->_key == '&')
		{
			for (size_t r = 0, r_max = vector_right.size(); r < r_max; r++)
				for (size_t l = 0, l_max = vector_left.size(); l < l_max; l++)
					if (vector_right[r] == vector_left[l])
					{
						tmp.push_back(vector_right[r]);
						break;
					}
		}
		else if (node->_key == '|')
		{
			for (const auto &c : vector_left)
				tmp.push_back(c);
			size_t l = 0;
			size_t l_max = vector_left.size();
			for (size_t r = 0, r_max = vector_right.size(); r < r_max; r++)
			{
				l = 0;
				for (; l < l_max; l++)
					if (vector_right[r] == vector_left[l])
						break;
				if (l == l_max)
					tmp.push_back(vector_right[r]);
			}
		}
		else if (node->_key == '^')
		{
			for (const auto &c : vector_left)
				tmp.push_back(c);
			size_t l = 0;
			size_t l_max = vector_left.size();
			for (size_t r = 0, r_max = vector_right.size(); r < r_max; r++)
			{
				l = 0;
				for (; l < l_max; l++)
					if (vector_right[r] == tmp[l])
					{
						tmp.erase(tmp.begin() + l);
						break;
					}						
				if (l == l_max)
					tmp.push_back(vector_right[r]);
			}
		}
		else if (node->_key == '>')
		{
			size_t i = 0;
			for (; i < vector_left.size(); ++i)
			{
				size_t i2 = 0;
				for (; i2 < vector_right.size(); ++i2)
				{
					if (vector_left[i] == vector_right[i2])
						break;
				}
				if (i2 == vector_right.size())
					break;
			}
			if (i == vector_left.size())
			{
				for (const auto &c : vector_right)
				{
					tmp.push_back(c);
				}
			}
		}
		else if (node->_key == '=')
		{
			if (vector_left.size() == vector_right.size())
			{
				size_t i = 0;
				for (; i < vector_left.size(); ++i)
				{
					size_t i2 = 0;
					for (; i2 < vector_right.size(); ++i2)
					{
						if (vector_left[i] == vector_right[i2])
							break;
					}
					if (i2 == vector_right.size())
						break;
				}
				if (i == vector_left.size())
				{
					for (const auto &c : vector_left)
					{
						tmp.push_back(c);
					}
				}
			}
		}
		else
		{
			throw std::runtime_error("Unreachable set operation");
		}
		return tmp;
	}
	else
		return (key_map.find(node->_key)->second);
}

Vec<i32>	Tree::result_key_map_sets(std::map<char, Vec<i32>> &key_map)
{
	// evol_negation_normal_form(_root); it is not logic!!!!
	return evol_key_map_sets(_root, key_map);
}

