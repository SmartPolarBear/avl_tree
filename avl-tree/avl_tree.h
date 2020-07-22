#pragma once
#include <cstdint>
#include <algorithm>

using std::max;

template<typename T>
class AVLTree
{
private:
	struct node
	{
		T key;
		size_t height;
		node* left, * right;
	};

	inline int subtree_height(node* n)
	{
		if (n == nullptr)
		{
			return 0;
		}
		else
		{
			return n->height;
		}
	}

	inline node* new_node(T key)
	{
		node* n = new node;
		n->key = key;
		n->left = nullptr;
		n->right = nullptr;
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
		node* y = x->left;
		node* t2 = y->left;

		y->left = x;
		x->right = t2;

		x->height = max(subtree_height(x->left), subtree_height(x->right)) + 1;
		y->height = max(subtree_height(y->left), subtree_height(y->right)) + 1;

		return y; // new root
	}

	inline int balance_factor(node* n)
	{
		if (n == nullptr)
		{
			return 0;
		}
		return subtree_height(n->left) - subtree_height(n->right);
	}


	inline node* min_node(node* root)
	{
		node& current = root;
		while (current->left)
			current = current->left;

		return current;
	}

	node* insert(node* root, T key)
	{
		if (root == nullptr)
		{
			return new_node(key);
		}

		if (key < root->key)
		{
			root->left = insert(root->left, key);
		}
		else if (key > node->key)
		{
			root->right = insert(root->right, key);
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
		auto factor = balance_factor(root);

		// left left
		if (factor > 1 && key < root->left->key)
		{
			return right_rotate(root);
		}

		// right right
		if (factor<-1 && key>root->right->key)
		{
			return left_rotate(root);
		}

		// left right
		if (factor > 1 && key > root->left->key)
		{
			root->left = left_rotate(root->left);
			return right_rotate(root);
		}

		// right left
		if (factor < -1 && key < root->right->key)
		{
			root->right = right_rotate(root->right);
			return left_rotate(root);
		}

		// no need to re-balance
		return root;

	}

	node* remove(node* root, T key)
	{
		if (root == nullptr)
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
			if (root->left == nullptr || root->right == nullptr)
			{
				node* victim = root->left ? root->left : root->right;
				if (victim == nullptr)
				{
					victim = root;
					root = nullptr;
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

		if (root == nullptr)
		{
			return root;
		}

		root->height = max(subtree_height(root->left), subtree_height(root->right)) + 1;

		auto factor = balance_factor(root);

		// Left Left Case  
		if (factor > 1 && balance_factor(root->left) >= 0)
		{
			return right_rotate(root);
		}

		// Left Right Case  
		if (factor > 1 && balance_factor(root->left) < 0)
		{
			root->left = leftRotate(root->left);
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
			root->right = rightRotate(root->right);
			return left_rotate(root);
		}

		return root;
	}

	node* find(node* root, T key)
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
			else if(key < iter->key)
			{
				return iter;
			}
		}

		return nullptr;
	}
public:
};