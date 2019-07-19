#include <iostream>
#include <fstream>

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

struct AccountRecord
{
	int recNum; //Record number
	int acctID; //Student identifier
	char firstName[10]; //First name
	char lastName[10]; //Last name
	char program[10]; //degree program of a student
	double cgpa; //Student’s CGPA
};

int main(void)
{
	BST bst_index;

	ifstream in_file("records.dat", ios::binary);

	if (!in_file.is_open())
	{
		cout << "Something went wrong while opening the file!\n";
		return -1;
	}

	while (true)
	{
		AccountRecord accRec;

		in_file.read(reinterpret_cast<char*>(&accRec), sizeof(AccountRecord));

		if (in_file.eof())
		{
			break;
		}

		cout << accRec.acctID << ' ' << accRec.firstName << ' ' << accRec.lastName << ' ' << accRec.program << ' ' << accRec.cgpa << '\n';
		BST_Node* new_node = new BST_Node(accRec.recNum, accRec.acctID, NULL, NULL);

		bst_index.insert(new_node);
	}

	bst_index.print();

	/* Search for Account ID in the BST Index */
	int acc_id_to_search;

	do
	{
		cout << "Enter an Account ID/Roll Number to search for (-1 to exit): ";
		cin >> acc_id_to_search;

		int record_number = bst_index.search(acc_id_to_search);

		if (record_number == -1)
		{
			cout << "Could not find " << acc_id_to_search << " in the database!\n";
			continue;
		}
		else if (record_number == -2)
		{
			cout << "The database is empty!\n Nothing to search in for.\n";
			continue;
		}

		// look for record_number in the binary file
		AccountRecord accRec;
		in_file.clear();
		in_file.seekg(sizeof(AccountRecord) * record_number);
		in_file.read(reinterpret_cast<char*>(&accRec), sizeof(AccountRecord));
		cout << accRec.acctID << ' ' << accRec.firstName << ' ' << accRec.lastName << ' ' << accRec.program << ' ' << accRec.cgpa << '\n';
	} while (acc_id_to_search != -1);

	in_file.close();

	return 0;
}
