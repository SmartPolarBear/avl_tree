// POJ3481.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define  _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdint>
#include <algorithm>

using namespace std;

template<class TKey, class TData>
class AVLTree
{
private:
	struct node
	{
		TKey key;
		TData data;

		size_t height;
		node* left, * right;
	};

	inline int subtree_height(node* n)
	{
		if (n == NULL)
		{
			return 0;
		}
		else
		{
			return n->height;
		}
	}

	inline node* new_node(TKey key, TData data)
	{
		node* n = new node;

		n->key = key;
		n->data = data;

		n->left = NULL;
		n->right = NULL;
		n->height = 1;

		return n;
	}

	inline node* right_rotate(node* y)
	{
		node* x = y->left;
		node* t2 = x->right;

		x->right = y;
		y->left = t2;

		y->height = max(subtree_height(y->left), subtree_height(y->right)) + 1;
		x->height = max(subtree_height(x->left), subtree_height(x->right)) + 1;

		return x; // new root
	}

	inline node* left_rotate(node* x)
	{
		node* y = x->right;
		node* t2 = y->left;

		y->left = x;
		x->right = t2;

		x->height = max(subtree_height(x->left), subtree_height(x->right)) + 1;
		y->height = max(subtree_height(y->left), subtree_height(y->right)) + 1;

		return y; // new root
	}

	inline int balance_factor(node* n)
	{
		if (n == NULL)
		{
			return 0;
		}
		return subtree_height(n->left) - subtree_height(n->right);
	}


	inline node* min_node(node* root)
	{
		node* current = root;
		while (current->left)
			current = current->left;

		return current;
	}

	node* insert(node* root, TKey key, TData data)
	{
		if (root == NULL)
		{
			return new_node(key, data);
		}

		if (key < root->key)
		{
			root->left = insert(root->left, key, data);
		}
		else if (key > root->key)
		{
			root->right = insert(root->right, key, data);
		}
		else
		{
			// We can't add equal values
			// TODO: exception
			return root;
		}

		// update height
		root->height = max(subtree_height(root->left), subtree_height(root->right)) + 1;

		// balance the tree
		int factor = balance_factor(root);

		// left left
		if (factor > 1 && root->left && key < root->left->key)
		{
			return right_rotate(root);
		}

		// right right
		if (factor<-1 && root->right && key>root->right->key)
		{
			return left_rotate(root);
		}

		// left right
		if (factor > 1 && root->left && key > root->left->key)
		{
			root->left = left_rotate(root->left);
			return right_rotate(root);
		}

		// right left
		if (factor < -1 && root->right && key < root->right->key)
		{
			root->right = right_rotate(root->right);
			return left_rotate(root);
		}

		// no need to re-balance
		return root;

	}

	node* remove(node* root, TKey key)
	{
		if (root == NULL)
		{
			return root;
		}

		if (key < root->key)
		{
			root->left = remove(root->left, key);
		}
		else if (key > root->key)
		{
			root->right = remove(root->right, key);
		}
		else
		{
			if (root->left == NULL || root->right == NULL)
			{
				node* victim = root->left ? root->left : root->right;
				if (victim == NULL)
				{
					victim = root;
					root = NULL;
				}
				else
				{
					*root = *victim;
				}

				delete victim;
			}
			else
			{
				node* victim = min_node(root->right);

				root->key = victim->key;
				root->right = remove(root->right, victim->key);
			}
		}

		if (root == NULL)
		{
			return root;
		}

		root->height = max(subtree_height(root->left), subtree_height(root->right)) + 1;

		int factor = balance_factor(root);

		// Left Left Case  
		if (factor > 1 && balance_factor(root->left) >= 0)
		{
			return right_rotate(root);
		}

		// Left Right Case  
		if (factor > 1 && balance_factor(root->left) < 0)
		{
			root->left = left_rotate(root->left);
			return right_rotate(root);
		}

		// Right Right Case  
		if (factor < -1 && balance_factor(root->right) <= 0)
		{
			return left_rotate(root);
		}

		// Right Left Case  
		if (factor < -1 && balance_factor(root->right) > 0)
		{
			root->right = right_rotate(root->right);
			return left_rotate(root);
		}

		return root;
	}

	node* find(node* root, TKey key)
	{
		node* iter = root;
		while (iter)
		{
			if (key > iter->key)
			{
				iter = iter->right;
			}
			else if (key < iter->key)
			{
				iter = iter->left;
			}
			else if (key == iter->key)
			{
				return iter;
			}
		}

		return NULL;
	}

	void clear(node* root)
	{
		if (root->left != NULL)
		{
			clear(root->left);
		}

		if (root->right != NULL)
		{
			clear(root->right);
		}

		delete root;
		root = NULL;
	}

	void print_max(node* n)
	{
		if (n == NULL)
		{
			printf("0\n");
			return;
		}

		node* iter = n;
		while (iter->right)
		{
			iter = iter->right;
		}


		printf("%d\n", iter->data);
		remove(iter->key);

	}

	void print_min(node* n)
	{
		if (n == NULL)
		{
			printf("0\n");
			return;
		}

		node* iter = n;
		while (iter->left)
		{
			iter = iter->left;
		}

		printf("%d\n", iter->data);
		remove(iter->key);

	}

private:
	node* root;

public:
	AVLTree() :root(NULL)
	{

	}

	~AVLTree()
	{
		clear();
		root = NULL;
	}


	void insert(TKey key, TData data)
	{
		root = insert(root, key, data);
	}

	void clear()
	{

	}

	void remove(TKey key)
	{
		root = remove(root, key);
	}

	TData& find(TKey key)
	{
		node* node = find(root, key);
		if (node == NULL)
		{
			insert(key, TData());
			node = find(root, key);
		}

		return node->data;
	}

	TData& operator[](TKey key)
	{
		return find(key);
	}

	void print_min()
	{
		print_min(root);
	}

	void print_max()
	{
		print_max(root);
	}
};

AVLTree< unsigned long long, int> tree;
int main()
{
	for (;;)
	{
		int c = 0;
		scanf("%d", &c);
		if (c == 1)
		{
			int k = 0;
			unsigned long long p = 0;
			scanf("%d %lld", &k, &p);
			tree.insert(p, k);
		}
		else if (c == 2)
		{
			tree.print_max();
		}
		else if (c == 3)
		{
			tree.print_min();
		}
		else if (c == 0)
		{
			break;
		}
	}
	return 0;
}
