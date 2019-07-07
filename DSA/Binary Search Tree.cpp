#include <iostream>
#include <fstream>
#include <string>
#include <forward_list>

using namespace std;

void get_tokens(string arr[], string line)
{
	size_t pos = line.find(" : ");
	arr[0] = line.substr(0, pos);
	arr[1] = line.substr(pos + 3);
}

class BST_Node
{
	string english;
	forward_list<string> urdu;

	BST_Node* left;
	BST_Node* right;

public:
	BST_Node(string name, BST_Node* left, BST_Node* right)
	{
		this->english = name;

		this->left = left;
		this->right = right;
	}

	void insert_urdu(string urdu)
	{
		this->urdu.push_front(urdu);
	}

	bool operator< (BST_Node node)
	{
		return this->english[0] < node.english[0];
	}

	friend class BST;
};

class BST
{
	BST_Node* root;
	string unit_name;

	void print_inorder(BST_Node* node)
	{
		if (node == NULL)
		{
			return;
		}

		this->print_inorder(node->left);
		cout << node->english << " : ";
		for (auto i : node->urdu)
			cout << i << ",";
		cout << '\n';
		this->print_inorder(node->right);
	}

	BST_Node* search_inorder(BST_Node* node, string english)
	{
		if (node == NULL)
		{
			return NULL;
		}

		if (english == node->english)
		{
			return node;
		}
		else if (english < node->english)
		{
			return this->search_inorder(node->left, english);
		}
		else if (english > node->english)
		{
			return this->search_inorder(node->right, english);
		}
		else
		{
			return NULL;
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
		else if (node->english == insert_on->english)
		{
			insert_on->insert_urdu(node->urdu.front());
			delete node;
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

	BST_Node* search(string to_find)
	{
		if (this->is_empty())
		{
			return NULL;
		}

		return this->search_inorder(this->root, to_find);
	}

	void print() // in-order
	{
		cout << this->unit_name << '\n';
		this->print_inorder(this->root);
		cout << '\n';
	}

	/* Util */
	bool is_empty()
	{
		return this->root == NULL;
	}

	void read_unit(ifstream& in_file)
	{
		getline(in_file, this->unit_name);
		// TODO: clear the tree
		this->root = NULL;

		string line;
		
		while (!in_file.eof())
		{
			getline(in_file, line);

			if (line.empty())
				break;

			string tokens[2]; // tokens[0] = urdu, tokens[1] = english
			get_tokens(tokens, line);

			BST_Node* temp = new BST_Node(tokens[1], NULL, NULL);

			temp->insert_urdu(tokens[0]);
			this->insert(temp);
		}
	}
};

int main(void)
{
	BST bst_index;

	ifstream in_file("input.txt");

	if (!in_file.is_open())
	{
		cout << "Something went wrong while opening the file!\n";
		return -1;
	}

	while (!in_file.eof())
	{
		bst_index.read_unit(in_file);
		bst_index.print();
		system("PAUSE");
	}

	in_file.close();

	return 0;
}
