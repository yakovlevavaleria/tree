#include <iostream> 
#include <string> 
#include <stdio.h>
#include <fstream> 
#include <stdexcept>
using namespace std;


template <typename Type>
struct Node
{
	Type value;
	Node<Type> *left;
	Node<Type> *right;
	Node(Type const& value) : value{ value }, left{ nullptr }, right{ nullptr } {}
};

template <typename Type>
class BinarySearchTree
{
private:
	Node<Type> *root;
public:
	BinarySearchTree()
	{
		root = nullptr;
	}
	~BinarySearchTree()
	{
		Delete(root);
	}
	void Delete(Node<Type> *node)
	{
		if (node)
		{
			Delete(node->left);
			Delete(node->right);
			delete node;
		}
		else return;
	}

	Type value_() const
	{
		return root->value;
	}

	Node<Type> *left_() const
	{
		return root->left;
	}
	Node<Type> *right_() const
	{
		return root->right;
	}
	Node<Type> *root_() const
	{
		return root;
	}

	void insert(const Type& value)
	{
		insert(root, value);
	}

	void insert(Node<Type> *&node, const Type& value)
	{
		if (!node)
		{
			node = new Node<Type>(value);
		}
		else
		{
			if (node->value > value)
			{
				insert(node->left, value);
			}
			if (node->value < value)
			{
				insert(node->right, value);
			}
			if (value == node->value)
			{
				throw logic_error(" \n");
			}
		}

	}

	Node<Type>  *search(const Type& value) const
	{
		Node<Type> *element = root;
		while (element)
		{
			if (element->value == value)
				break;
			else
			{
				if (element->value < value)
					element = element->right;
				else
					element = element->left;
			}
		}
		return element;
	}

	bool check_search(const Type& value)
	{
		Node<Type> *node;
		node = search(value);
		if (node) return true;
		else return false;

	}

	void read_of_file(const string file)
	{
		ifstream fin;
		unsigned int n;
		fin.open(file);
		if (!fin.is_open())
		{
			throw logic_error(" The file is not find ");
		}
		Delete(root);
		if (fin.is_open())
		{
			fin >> n;
			Type new_element;
			for (unsigned int i = 0; i < n; ++i)
			{
				fin >> new_element;
				insert(new_element);
			}
		}
		fin.close();
	}

	void print_to_file(const string file)
	{
		ofstream fout;
		fout.open(file);
		if (!fout.is_open())
		{
			throw logic_error(" The file is not find ");
		}
		unsigned int size_ = size(root);
		if (size_ == 0)
		{
			throw logic_error(" The tree is empty ");
		}
		fout << size_ << "\t";
		print_to_file(root, fout);
		fout.close();
	}

	void print_to_file(Node<Type> *node, ostream&stream)const
	{
		if (node)
		{
			stream << node->value << " ";
			print_to_file(node->left, stream);
			print_to_file(node->right, stream);
		}
	}

	unsigned int size(Node<Type> *node)const
	{
		unsigned int size_ = 0;
		if (node)
		{
			size_ = size(node->left) + 1 + size(node->right);
		}
		return size_;
	}
	void print(ostream&stream)const
	{
		print(root, stream, 0);
	}
	void print(Node<Type> *node, ostream&stream, unsigned int level)const
	{
		Node<Type> *element = node;
		if (element)
		{
			print(element->right, stream, level + 1);
			for (unsigned int i = 0; i < level; ++i)
				stream << '-';
			stream << element->value << endl;
			print(element->left, stream, level + 1);
		}
	}

	Node<Type> *pred_(const Type&value)
	{
		return pred_(root, value);
	}

	Node<Type> *pred_(Node<Type> *&node, const Type& value)
	{
		if (check_search(value))
		{
			if (value < node->value)
			{
				if (value != node->left->value)
				{
					return pred_(node->left, value);
				}
				else return node;
			}
			else if (value > node->value)
			{
				if (value != node->right->value)
					return pred_(node->right, value);
				else return node;
			}
			else return nullptr;
		}
		else return nullptr;
	}

	void delete_value(const Type& value)
	{
		if (check_search(value) == false)
		{
			throw logic_error(" There is not element in the tree ");

		}
		Node<Type> *element = search(value);
		Node<Type> *pred = pred_(value);
		if (element->left == nullptr && element->right == nullptr)
		{
			if (pred->left == element)
			{
				pred->left = nullptr;
			}
			else pred->right = nullptr;
			element = nullptr;
		}
		else if (element->right == nullptr)
		{
			if (pred->left == element)
			{
				pred->left = element->left;
			}
			else pred->right = element->left;
			element = nullptr;
		}
		else
		{
			Node<Type> *min = element->right;
			while (min->left)
			{
				min = min->left;
			}
			Type b = min->value;
			element->value = b;
			delete_value(min->value);
		}
	}

};
