#include <iostream>
#include <algorithm>

using namespace std;

class Node
{
private:
	int value;

	Node* left;
	Node* right;
	Node* parent;

public:
	Node(int value, Node* left = NULL, Node* right = NULL, Node* parent = NULL)
	{
		this->value = value;

		this->left = left;
		this->right = right;
		this->parent = parent;
	}

	int get_value() const
	{
		return this->value;
	}

	friend class AVL_Tree;
};

class AVL_Tree
{
private:
	Node* root;

	void print_inorder(Node* node)
	{
		if (node == NULL)
			return;

		this->print_inorder(node->left);
		cout << node->value << ' ';
		this->print_inorder(node->right);
	}

public:
	AVL_Tree()
	{
		this->root = NULL;
	}

	void insert(Node* insert_me)
	{
		if (this->is_empty())
		{
			this->root = insert_me;
			return;
		}

		Node* it = this->root;

		do
		{
			if (insert_me->value < it->value)
				if (it->left == NULL)
				{
					insert_me->parent = it;
					it->left = insert_me;
					cout << "left\n";
					break;
				}
				else
					it = it->left;
			else if (insert_me->value > it->value)
				if (it->right == NULL)
				{
					insert_me->parent = it;
					it->right = insert_me;
					cout << "right\n";
					break;
				}
				else
					it = it->right;
		} while (it != NULL);
		
		

		// balance upto root
		while (it != NULL)
		{
			cout << "nv: " << it->value << ' ';
			cout << "bf: " << this->balance_factor(it) << '\n';
			this->root = this->balance(it);
			it = it->parent;
		}
	}

	void print() // in-order
	{
		//this->print_inorder(this->root);
		this->pre_order(this->root);
		cout << '\n';
	}

	void pre_order(Node* node)
	{
		if (node == NULL)
			return;
		cout << node->value << "  ";
		pre_order(node->left);
		pre_order(node->right);

	}

	int height(Node* node)
	{
		int h = 0;

		if (node != NULL)
		{
			int l_height = height(node->left);
			int r_height = height(node->right);
			int max_height = max(l_height, r_height);
			h = max_height + 1;
		}

		return h;
	}

	Node* balance(Node* node)
	{
		// left heavy
		if (this->balance_factor(node) > 1)
		{
			if (this->balance_factor(node->left) > 0) // LL
			{
				node = this->right_rotate(node);
				cout << "right rot\n";
			}
			else
				; // left-right
		}
		// right heavy
		else if (this->balance_factor(node) < -1)
		{
			if (this->balance_factor(node->right) > 0)
				;//this->right_left_rotate(node);
			else
			{
				node = this->left_rotate(node);
				cout << "left rot\n";
			}
				
		}

		return node;
	}

	Node* left_rotate(Node* node)
	{
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node;

		temp->parent = node->parent;
		node->parent = temp;

		return temp;
	}

	Node* right_rotate(Node* node)
	{
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node;

		temp->parent = node->parent;
		node->parent = temp;

		return temp;
	}

	int balance_factor(Node* node)
	{
		return this->height(node->left) - this->height(node->right);
	}

	bool is_empty() const
	{
		return this->root == NULL;
	}
};

int main(void)
{
	AVL_Tree avl;

	avl.insert(new Node(1));
	avl.insert(new Node(2));
	avl.insert(new Node(3));

	avl.print();

	return 0;
}