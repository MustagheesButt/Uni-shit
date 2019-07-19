#include <iostream>

using namespace std;

class BST_Node
{
	friend class BST;

	int id;
	int account_id;

	BST_Node* left;
	BST_Node* right;

public:
	BST_Node(int id, int account_id, BST_Node* left, BST_Node* right)
	{
		this->id = id;
		this->account_id = account_id;

		this->left = left;
		this->right = right;
	}

	bool operator< (BST_Node node)
	{
		return this->account_id < node.account_id;
	}
};

class BST
{
	BST_Node* root;

	void print_inorder(BST_Node* node)
	{
		if (node == NULL)
		{
			return;
		}

		this->print_inorder(node->left);
		cout << node->account_id << ' ';
		this->print_inorder(node->right);
	}

	int search_inorder(BST_Node* node, int account_id)
	{
		if (node == NULL)
		{
			return -1;
		}

		if (account_id == node->account_id)
		{
			return node->id;
		}
		else if (account_id < node->account_id)
		{
			return this->search_inorder(node->left, account_id);
		}
		else if (account_id > node->account_id)
		{
			return this->search_inorder(node->right, account_id);
		}
		else
		{
			return -1;
		}
	}

public:
	BST()
	{
		this->root = NULL;
	}

	void insert(BST_Node* node, BST_Node* insert_on = NULL)
	{
		if (insert_on == NULL)
		{
			insert_on = this->root;
		}

		if (this->is_empty())
		{
			this->root = node;
		}
		else if (*node < *insert_on)
		{
			if (insert_on->left == NULL)
				insert_on->left = node;
			else
				this->insert(node, insert_on->left);
		}
		else // assuming two nodes equaln't
		{
			if (insert_on->right == NULL)
				insert_on->right = node;
			else
				this->insert(node, insert_on->right);
		}
	}

	int search(int account_id)
	{
		if (this->is_empty())
		{
			return -2;
		}

		return this->search_inorder(this->root, account_id);
	}

	void print() // in-order
	{
		this->print_inorder(this->root);
		cout << '\n';
	}

	/* Util */
	bool is_empty()
	{
		return this->root == NULL;
	}
};
